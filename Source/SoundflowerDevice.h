#pragma once

#include <IOKit/audio/IOAudioDevice.h>

#define AUDIO_ENGINES_KEY				"AudioEngines"
#define DESCRIPTION_KEY					"Description"
#define BLOCK_SIZE_KEY					"BlockSize"
#define NUM_BLOCKS_KEY					"NumBlocks"
#define NUM_STREAMS_KEY					"NumStreams"
#define FORMATS_KEY						"Formats"
#define SAMPLE_RATES_KEY				"SampleRates"
#define SEPARATE_STREAM_BUFFERS_KEY		"SeparateStreamBuffers"
#define SEPARATE_INPUT_BUFFERS_KEY		"SeparateInputBuffers"
#define SoundflowerDevice				com_cycling74_driver_SoundflowerDevice

#define NUM_CHANS 64

class SoundflowerEngine;

class SoundflowerDevice : public IOAudioDevice
{
    OSDeclareDefaultStructors(SoundflowerDevice)
    friend class SoundflowerEngine;
    
	// class members
	
    static const SInt32 kVolumeMax;
    static const SInt32 kGainMax;

	
	// instance members

    SInt32 mVolume[NUM_CHANS+1];
    SInt32 mMuteOut[NUM_CHANS+1];
    SInt32 mMuteIn[NUM_CHANS+1];
    SInt32 mGain[NUM_CHANS+1];

	
	// methods
	
    virtual bool initHardware(IOService *provider) override;
    virtual bool createAudioEngines();
    virtual bool initControls(SoundflowerEngine *audioEngine);
    
    static  IOReturn volumeChangeHandler(IOService *target, IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn volumeChanged(IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue);
    
    static  IOReturn outputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn outputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);

    static  IOReturn gainChangeHandler(IOService *target, IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn gainChanged(IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue);
    
    static  IOReturn inputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn inputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    
};
