/* Edge Impulse ingestion SDK
 * Wio Terminal dedicated: real-time audio inference using DMA.
 * This final optimized version fully reflects the instructions from document p.34-37.
 */

#define EIDSP_QUANTIZE_FILTERBANK   0
#define EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW 4

/* Includes ---------------------------------------------------------------- */
#include <Audio_scene_recognition_with_microphone_inferencing.h>

// Settings
#define DEBUG 1
enum { ADC_BUF_LEN = 4096 }; // Size of one of the DMA double buffers
static const int debug_pin = 1;

// DMAC descriptor structure
typedef struct {
    uint16_t btctrl;
    uint16_t btcnt;
    uint32_t srcaddr;
    uint32_t dstaddr;
    uint32_t descaddr;
} dmacdescriptor;

/** Audio buffers, pointers and selectors */
typedef struct {
    signed short *buffers[2];
    unsigned char buf_select;
    unsigned char buf_ready;
    unsigned int buf_count;
    unsigned int n_samples;
} inference_t;

static inference_t inference;
static bool debug_nn = false;
static int print_results = -(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW);

// Globals - DMA and ADC
volatile uint8_t recording = 0;
uint16_t adc_buf_0[ADC_BUF_LEN];
uint16_t adc_buf_1[ADC_BUF_LEN];
volatile dmacdescriptor wrb[DMAC_CH_NUM] __attribute__ ((aligned (16)));
dmacdescriptor descriptor_section[DMAC_CH_NUM] __attribute__ ((aligned (16)));
dmacdescriptor descriptor __attribute__ ((aligned (16)));

// High pass butterworth filter
class FilterBuHp1 {
public:
    FilterBuHp1() { v[0] = 0.0; }
    float step(float x) {
        v[0] = v[1];
        v[1] = (9.621952458291035404e-1f * x) + (0.92439049165820696974f * v[0]);
        return (v[1] - v[0]);
    }
private:
    float v[2];
};
FilterBuHp1 filter;

/**
 * Callback called when the DMA buffer is full
 */
static void audio_rec_callback(uint16_t *buf, uint32_t buf_len) {
    if (recording) {
        for (uint32_t i = 0; i < buf_len; i++) {
            // Convert 12-bit unsigned ADC value to 16-bit PCM (signed) and apply high-pass filter
            inference.buffers[inference.buf_select][inference.buf_count++] = filter.step(((int16_t)buf[i] - 1024) * 16);
            if (inference.buf_count >= inference.n_samples) {
                inference.buf_select ^= 1;
                inference.buf_count = 0;
                inference.buf_ready = 1;
            }
        }
    }
}

/**
 * Interrupt Service Routine (ISR) for DMAC 1
 */
void DMAC_1_Handler() {
    static uint8_t count = 0;
    if (DMAC->Channel[1].CHINTFLAG.bit.SUSP) {
#if DEBUG
        digitalWrite(debug_pin, HIGH);
#endif
        // Restart DMAC on channel 1 and clear SUSP interrupt flag
        DMAC->Channel[1].CHCTRLB.reg = DMAC_CHCTRLB_CMD_RESUME;
        DMAC->Channel[1].CHINTFLAG.bit.SUSP = 1;
        
        // Determine which buffer filled up and process it
        if (count) {
            audio_rec_callback(adc_buf_0, ADC_BUF_LEN);
        } else {
            audio_rec_callback(adc_buf_1, ADC_BUF_LEN);
        }
        count = (count + 1) % 2;
#if DEBUG
        digitalWrite(debug_pin, LOW);
#endif
    }
}

/**
 * Configure DMA and ADC for 16kHz sampling
 */
void config_dma_adc() {
    // Specify descriptor locations
    DMAC->BASEADDR.reg = (uint32_t)descriptor_section;
    DMAC->WRBADDR.reg = (uint32_t)wrb;
    // Enable DMAC peripheral
    DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);
    // Set trigger on TC5 timer overflow
    DMAC->Channel[1].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(TC5_DMAC_ID_OVF) | DMAC_CHCTRLA_TRIGACT_BURST;

    // Set up circular descriptors
    descriptor.descaddr = (uint32_t)&descriptor_section[1];
    descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;
    descriptor.dstaddr = (uint32_t)adc_buf_0 + sizeof(uint16_t) * ADC_BUF_LEN;
    descriptor.btcnt = ADC_BUF_LEN;
    descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD | DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_VALID | DMAC_BTCTRL_BLOCKACT_SUSPEND;
    memcpy(&descriptor_section[0], &descriptor, sizeof(descriptor));

    descriptor.descaddr = (uint32_t)&descriptor_section[0];
    descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;
    descriptor.dstaddr = (uint32_t)adc_buf_1 + sizeof(uint16_t) * ADC_BUF_LEN;
    descriptor.btcnt = ADC_BUF_LEN;
    descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD | DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_VALID | DMAC_BTCTRL_BLOCKACT_SUSPEND;
    memcpy(&descriptor_section[1], &descriptor, sizeof(descriptor));

    // Configure NVIC priority
    NVIC_SetPriority(DMAC_1_IRQn, 0);
    NVIC_EnableIRQ(DMAC_1_IRQn);
    DMAC->Channel[1].CHINTENSET.reg = DMAC_CHINTENSET_SUSP;

    // ADC configuration (AIN12 for Microphone)
    ADC1->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_AIN12_Val;
    while(ADC1->SYNCBUSY.bit.INPUTCTRL);
    ADC1->SAMPCTRL.bit.SAMPLEN = 0x00;
    while(ADC1->SYNCBUSY.bit.SAMPCTRL);
    ADC1->CTRLA.reg = ADC_CTRLA_PRESCALER_DIV128;
    ADC1->CTRLB.reg = ADC_CTRLB_RESSEL_12BIT | ADC_CTRLB_FREERUN;
    while(ADC1->SYNCBUSY.bit.CTRLB);
    ADC1->CTRLA.bit.ENABLE = 1;
    while(ADC1->SYNCBUSY.bit.ENABLE);
    ADC1->SWTRIG.bit.START = 1;
    while(ADC1->SYNCBUSY.bit.SWTRIG);

    // Start DMA channel 1
    DMAC->Channel[1].CHCTRLA.bit.ENABLE = 1;

    // Configure Timer/Counter 5 for 16kHz sampling
    GCLK->PCHCTRL[TC5_GCLK_ID].reg = GCLK_PCHCTRL_CHEN | GCLK_PCHCTRL_GEN_GCLK1;
    TC5->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ;
    TC5->COUNT16.CC[0].reg = 3000 - 1; // (48MHz / 16000) - 1
    while (TC5->COUNT16.SYNCBUSY.bit.CC0);
    TC5->COUNT16.CTRLA.bit.ENABLE = 1;
    while (TC5->COUNT16.SYNCBUSY.bit.ENABLE);
}

/**
 * Data acquisition callback for inference engine
 */
static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr) {
    numpy::int16_to_float(&inference.buffers[inference.buf_select ^ 1][offset], out_ptr, length);
    return 0;
}

void setup() {
    Serial.begin(115200);
    while (!Serial);

#if DEBUG
    pinMode(debug_pin, OUTPUT);
#endif

    Serial.println("Wio Terminal Audio Inference Start");

    run_classifier_init();

    // Allocate double buffers for inference
    inference.buffers[0] = (int16_t *)malloc(EI_CLASSIFIER_SLICE_SIZE * sizeof(int16_t));
    inference.buffers[1] = (int16_t *)malloc(EI_CLASSIFIER_SLICE_SIZE * sizeof(int16_t));

    if (inference.buffers[0] == NULL || inference.buffers[1] == NULL) {
        ei_printf("ERROR: Failed to allocate inference buffers\n");
        return; 
    }

    inference.buf_select = 0;
    inference.buf_count = 0;
    inference.n_samples = EI_CLASSIFIER_SLICE_SIZE;
    inference.buf_ready = 0;

    // Start DMA configuration
    config_dma_adc();
    recording = 1;
}

void loop() {
    // Wait for data to accumulate (DMA to become full)
    if (inference.buf_ready == 0) {
        delay(1);
        return;
    }
    inference.buf_ready = 0;

    signal_t signal;
    signal.total_length = EI_CLASSIFIER_SLICE_SIZE;
    signal.get_data = &microphone_audio_signal_get_data;

    ei_impulse_result_t result = {0};

    // Run continuous inference
    EI_IMPULSE_ERROR r = run_classifier_continuous(&signal, &result, debug_nn);
    if (r != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", r);
        return;
    }

    // Output inference results for each model window
    if (++print_results >= (EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW)) {
        ei_printf("Predictions (DSP: %d ms., Classification: %d ms.): \n",
            result.timing.dsp, result.timing.classification);
        for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
            ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
        }
        print_results = 0;
    }
}
