
#pragma once

#include <IOKit/audio/IOAudioEngine.h>
#include "SoundflowerDevice.h"


class SoundflowerEngine : public IOAudioEngine
{
    OSDeclareDefaultStructors(SoundflowerEngine)
    
	UInt32				mBufferSize;
	void*				mBuffer;				// input/output buffer
    float*				mThruBuffer;			// intermediate buffer to pass in-->out
	
	IOAudioStream*		outputStream;
	IOAudioStream*		inputStream;
    	
	UInt32				mLastValidSampleFrame;
    
    IOTimerEventSource*	timerEventSource;
    
    UInt32				blockSize;				// In sample frames -- fixed, as defined in the Info.plist (e.g. 8192)
    UInt32				numBlocks;
    UInt32				currentBlock;
    
    UInt64				blockTimeoutNS;
    UInt64				nextTime;				// the estimated time the timer will fire next

    bool				duringHardwareInit;
    
	float             logTable[100] ; // Lookup for logarithmic volume scaling.

	
public:

    virtual bool init(OSDictionary *properties) override;
    virtual void free() override;

    void initLogTable();
    
    virtual bool initHardware(IOService *provider) override;
    
    virtual bool createAudioStreams(IOAudioSampleRate *initialSampleRate);

    virtual IOReturn performAudioEngineStart() override;
    virtual IOReturn performAudioEngineStop() override;
    
    virtual UInt32 getCurrentSampleFrame() override;
    
    virtual IOReturn performFormatChange(IOAudioStream *audioStream, const IOAudioStreamFormat *newFormat, const IOAudioSampleRate *newSampleRate) override;

    virtual IOReturn clipOutputSamples(const void *mixBuf, void *sampleBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream) override;
    virtual IOReturn convertInputSamples(const void *sampleBuf, void *destBuf, UInt32 firstSampleFrame, UInt32 numSampleFrames, const IOAudioStreamFormat *streamFormat, IOAudioStream *audioStream) override;
    
    static void ourTimerFired(OSObject *target, IOTimerEventSource *sender);
    
};
