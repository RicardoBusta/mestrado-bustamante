#ifndef CONSTANTS_H
#define CONSTANTS_H

const float kMinFov = 60.0f;
const float kMaxFov = 120.0f;
const float kDefaultFov = 90.0f;

const float kMinNear = 0.01f;
const float kMaxNear = 5.0f;
const float kDefaultNear = 1.0f;

const float kMinFar = 5.0f;
const float kMaxFar = 100.0f;
const float kDefaultFar = 30.0f;

const float kDefaultRatio = 1.0f;

const int kImageSize = 1000;
const int kImageMovingSize = 100;

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#endif // CONSTANTS_H
