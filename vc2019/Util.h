#pragma once
#include "cinder/Cinder.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "time.h"

template <typename T>
static T RandRange(T max, T min) {
	return (rand() % (max + 1 - min)) + min;
};
template <typename T>
static T Remap(T value, T from1, T from2, T to1, T to2) {
	return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
};

static float DeltaTime() {
	return (ci::app::getElapsedSeconds()/ci::app::getElapsedFrames());
}