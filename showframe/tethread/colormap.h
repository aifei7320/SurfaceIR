#ifndef COLORMAP
#define COLORMAP
#include "opencv2/core/core.hpp"

using namespace cv;

namespace i3{
namespace I3ColorMap{
enum{
    WhiteHot = 0,
    BlackHot,
    Iron,
    BlueRed,
    Medical,
    Purple,
    PurpleYellow,
    DarkBlue,
    Cyan,
    Rainbow,
    Autumn,
    Bone,
    Jet,
    Winter,
    Ocean,
    Summer,
    Spring,
    Cool,
    HSV,
    Hot,
};
}
}

extern Mat				m_lutBlackHot;
extern Mat				m_lutBlueRed;
extern Mat				m_lutIron;
extern Mat				m_lutMedical;
extern Mat				m_lutPurple;
extern Mat				m_lutPurpleYellow;
extern Mat				m_lutDarkBlue;
extern Mat				m_lutCyan;
extern Mat				m_lutRainbow;

void SetColorTable();
void SetBlackHotColorTable();
void SetIronColorTable();
void SetBlueRedColorTable();
void SetMedicalColorTable();
void SetPurpleColorTable();
void SetPurpleYellowColorTable();
void SetDarkBlueColorTable();
void SetCyanColorTable();
void SetRainbowColorTalbe();

#endif // COLORMAP

