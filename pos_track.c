// Just using Trapezoidal Integral Functions

#include <stdio.h>

float computeTrapz(float a, float b, float dt) {
	
	float trapz;
	
	trapz = (a + b) * dt / 2.0;
	
	return trapz;
}

int main (void) {
	
	#define ACCELFILE	"accelfile.txt"
	
	FILE *accelFile;
	accelFile = fopen(ACCELFILE, "r");
	
	float vALast[3], pALast[3]={0,0,0};
	float aA[3]={0,0,0}, vA[3]={0,0,0}, pA[3]={0,0,0};
	float dt=1;
	
	while (!feof(accelFile)) {
		
		float aX, aY, aZ;

		fscanf(accelFile, "%f %f %f", &aX, &aY, &aZ);
		
		aA[0] = aX;
		aA[1] = aY;
		aA[2] = aZ;
		
		vALast[0] = aA[0];
		vALast[1] = aA[1];
		vALast[2] = aA[2];

		for (int i = 0; i < 3; i++) {
			vA[i] += computeTrapz(vALast[i], aA[i], dt);
			pA[i] += computeTrapz(pALast[i], vA[i], dt);
			vALast[i] = aA[i];
			pALast[i] = vA[i];
		}
	}
	
	fclose(accelFile);
	
	for (int i = 0; i < 3; i++) {
		printf("%.2f, %.2f, %.2f\n", aA[i], vA[i], pA[i]);
	}
	
	return 0;
}
