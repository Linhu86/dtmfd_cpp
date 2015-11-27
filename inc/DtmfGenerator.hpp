#ifndef __DTMF_GENERATOR_HPP__
#define __DTMF_GENERATOR_HPP__

typedef unsigned int   uint32;
typedef signed int     int32;
typedef unsigned short uint16;
typedef signed short   int16;

class DtmfGenerator{

  // FrameSize - Size of frame, DurationPush - duration pushed button in ms
  // DurationPause - duration pause between pushed buttons in ms
  public:
    DtmfGenerator(int32 FrameSize, int32 DurationPush=70, int32 DurationPause=50);
    ~DtmfGenerator();

    //That function will be run on each outcoming frame
    void dtmfGenerating(int16 out[]);

    int32 transmitNewDialButtonsArray[], uint32 lengthDialButtonsArray);

    void dtmfGenerationReset()
    {
      countLengthDialButtonArray = 0;
      count = 0;
      readyFlag = 1;
    }

    int32 getReadyFlag() const { return readyFlag? 1:0; }

  private:
    static const int16 tempCoeff[8];
    int32  countDurationPushButton;
    int32  countDurationPause;
    int32  tempCountDurationPushButton;
    int32  tempCountDurationPause;
    int32  readyFlag;
    char   pushDialButton[20];
    uint32 countLengthDialButtonArray;
    uint32 count;
    int32  sizeOfFrame;

    short  tempCoeff1, tempCoeff2;
    int32  y1_1, y1_2, y2_1, y2_2;

};



#endif

