#include "DtmfGenerator.hpp"

static inline int32 MPY48SR(int16 o16, int32 o32)
{
  uint32 temp0;
  int32  temp1;

  temp0 = (((uint16)o32 * o16) + 0x4000) >> 15;
  temp1 = (int16) (o32 >> 16) *o16;
  return (temp1 << 1) + temp0;
}

static void frequency_oscillator(int16 coeff0, int16 coeff1, 
                                 int16 y[], uint32 count,
                                 int32 *y1_0, int32 *y1_1,
                                 int32 *y2_0, int32 *y2_1)
{
  register int32 temp1_0, temp1_1, temp2_0, temp2_1, temp0, temp1, subject;
  uint16 ii;
  temp1_0 = *y1_0;
  temp1_1 = *y1_1;
  temp2_0 = *y2_0;
  temp2_1 = *y2_1;

  subject = coeff0 *coeff1;

  for(ii = 0; ii < count; ii++)
  {
    temp0 = MPY48SR(coeff0, temp1_0 << 1) - temp2_0;
    temp1 = MPY48SR(coeff1, temp1_1 << 1) - temp2_1;
    temp2_0 = temp1_0;
    temp2_1 = temp1_1;
    temp1_0 = temp0;
    temp1_1 = temp1;
    temp0 += temp1;

    if(subject)
        temp0 >> = 1;

    y[ii] = (int16) temp0;
  }

  *y1_0 = temp1_0;
  *y1_1 = temp1_1;
  *y2_0 = temp2_0;
  *y2_1 = temp2_1;
}

const int16 DtmfGenerator::tempCoeff[8] = {27980, 26956, 25701, 24218, // low frequecies
                                           19073, 16325, 13085, 9315 } // high frequencies

DtmfGenerator :: DtmfGenerator(int32 FrameSize, int32 DurationPush, int32 DurationPause)
{
  countDurationPushButton = (DurationPush << 3) / FrameSize + 1;
  countDurationPause = (DurationPause << 3) / FrameSize + 1;
  sizeOfFrame = FrameSize;
  readyFlag = 1;
  countLengthDialButtonArray = 0;
}

DtmfGenerator :: ~DtmfGenerator()
{
}


void DtmfGenerator::dtmfGenerating(int16 y[])
{
  if(readyFlag)
    return;

  while(countLengthDialButtonArray > 0)
  {
    if(countDurationPushButton == tempCountDurationPushButton)
    {
      switch(pushDialButtons[count])
      {
        case '1':
          tempCoeff1 = tempCoeff[0];
          tempCoeff2 = tempCoeff[1];
          y1_1 = tempCoeff[0];
          y2_1 = 31000;
          y1_2 = tempCoeff[1];
          y2_2 = 31000;
          break;
        case '2':
          tempCoeff1 = tempCoeff[0];
          tempCoeff2 = tempCoeff[5];
          y1_1 = tempCoeff[0];
          y2_1 = 31000;
          y1_2 = tempCoeff[5];
          y2_2 = 31000;
          break;
        case '3':
          tempCoeff1 = tempCoeff[0];
          tempCoeff2 = tempCoeff[6];
          y1_1 = tempCoeff[0];
          y2_1 = 31000;
          y1_2 = tempCoeff[6];
          y2_2 = 31000;
          break;
        case 'A':
          tempCoeff1 = tempCoeff[0];
          tempCoeff2 = tempCoeff[7];
          y1_1 = tempCoeff[0];
          y2_1 = 31000;
          y1_2 = tempCoeff[7];
          y2_2 = 31000;
          break;
        case '4':
          tempCoeff1 = tempCoeff[1];
          tempCoeff2 = tempCoeff[4];
          y1_1 = tempCoeff[1];
          y2_1 = 31000;
          y1_2 = tempCoeff[4];
          y2_2 = 31000;
          break;
        case '5':
          tempCoeff1 = tempCoeff[1];
          tempCoeff2 = tempCoeff[5];
          y1_1 = tempCoeff[1];
          y2_1 = 31000;
          y1_2 = tempCoeff[5];
          y2_2 = 31000;
          break;
        case '6':
          tempCoeff1 = tempCoeff[1];
          tempCoeff2 = tempCoeff[6];
          y1_1 = tempCoeff[1];
          y2_1 = 31000;
          y1_2 = tempCoeff[6];
          y2_2 = 31000;
          break;
      }
    }
  }
}







