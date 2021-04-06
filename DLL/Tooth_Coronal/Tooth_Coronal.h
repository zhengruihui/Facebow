#pragma once
extern "C" __declspec(dllexport) void Tooth_Coronal(float *Left_X, float *Left_Y, float *Left_Z,
	float *Right_X, float *Right_Y, float *Right_Z,
	int len_left, int len_right,
	float *Coronal_Left_X, float *Coronal_Left_Y, float *Coronal_Right_X, float *Coronal_Right_Y,
	int *len_out);