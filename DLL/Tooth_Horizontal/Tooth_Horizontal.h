#pragma once
extern "C" __declspec(dllexport) void Tooth_Horizontal(float *Forward_X, float *Forward_Y, float *Forward_Z,
	float *Left_X, float *Left_Y, float *Left_Z,
	float *Right_X, float *Right_Y, float *Right_Z,
	int len_forward, int len_left, int len_right,
	float *Horizontal_Forward_X, float *Horizontal_Forward_Y,
	float *Horizontal_Left_X, float *Horizontal_Left_Y,
	float *Horizontal_Right_X, float *Horizontal_Right_Y,
	int *len_out);