#include "gap_sino.h"

/** @brief make a gap sinogram

@param head_num : total heads number
@param detec_width : detector width (unit : mm)
@param detector_num : detector number in a head
@param gap_angle : gap angle
@param resolution : to be saved sinogram, input image resolution
@param filename : save sinogram file name (default : "sinogram.i")
@return : void
*/
void gap_sino(int head_num,float detector_width,float xrSampling_mm ,int detector_num, float gap_angle,int imageWidth,char* filename)
{ 
	int totalDetectorNum=0;
	float rtheta = 0; 
	//int xrNum = (2 * int(sqrt(2 * pow(imageWidth / 2, 2))) + 5);
	// In Matlab , int xrNum = 2 * round(sqrt(2 * pow(imageWidth - round(((imageWidth - 1) / 2.)-0.5) - 1, 2)) + 0.5) + 3;
	int xrNum = 2 * round(sqrt(2 * pow(imageWidth - round(((imageWidth - 1) / 2.) - 0.5) - 1, 2)) + 0.5) + 3;
	int limitRadial = imageWidth / 2;

	float head_size = detector_num*detector_width;	///< calculate a head size according to detector number and width
	float headTohead = head_size / tan(degreeToradian((180 / head_num) - gap_angle / 2));	///< head to head distance
	float detector_interval = detector_width;
	float xrSamplingInterval_mm = xrSampling_mm;	


	totalDetectorNum = detector_num*head_num;
	int totalAngleViewNum = totalDetectorNum / 2;
	rtheta = 180.f/(totalAngleViewNum);


	FILE* fileID;	///< variable for save file 
	polPoint* LORs = (polPoint*)calloc(detector_num*detector_num*(head_num-3)*head_num, sizeof(polPoint));	///< variable to save LOR's polar coordinate 
	head* heads = (head*)calloc(head_num, sizeof(head));	///< variable to save heads 
	for (int i = 0; i < head_num; i++) {
		heads[i].det = (carPoint*)calloc(detector_num, sizeof(carPoint));	///< variable to save totalDetectorNum cartesian coordinate
	}

	/////////////////////////////////////////////////////////////////////
	/// collocation detection	
	for (int i = 0; i < detector_num; i++) {
		heads[0].det[i].x = 0 + (detector_interval / 2.) + i*detector_interval - head_size/2.;
		heads[0].det[i].y = headTohead / 2.;
	}
	for (int j = 1; j < head_num; j++) {
		for (int i = 0; i < detector_num; i++) {
			float rotAngle = 360. / head_num;
			heads[j].det[i] = rotClock(heads[j-1].det[i], rotAngle);
		}
	}
	/////////////////////////////////////////////////////////////////////
	fileID = fopen("detector_LORs.txt", "w");
	/////////////////////////////////////////////////////////////////////
	// calculate LORs
	int index = 0;	///< variable for LORs number index
	float maxRadial = 0.;	///< to check maximum radial distance
	float maxTheta = 0.;	///< to check maximum theta angle
	for (int i = 0; i < head_num; i++) {
		for (int j = 0; j < head_num - 3; j++) {
			int indHead = i + j + 2;
			if (indHead >= head_num)	indHead = indHead - head_num;
			for (int k = 0; k < detector_num; k++) {
				for (int l = 0; l < detector_num; l++) {
					float gradient = (heads[i].det[k].y - heads[indHead].det[l].y)
						/(heads[i].det[k].x-heads[indHead].det[l].x);
					float radial = (-gradient*heads[i].det[k].x + heads[i].det[k].y) 
						/ sqrt(pow(gradient, 2) + 1);
					float theta = radianTodegree(atan(gradient)) >= 0 ? radianTodegree(atan(gradient)) : radianTodegree(atan(gradient)) + 180;
					float temp = radial;
					if (maxRadial < temp)	///< update maximum radial	
						maxRadial = temp;
					temp = theta;
					if (maxTheta < temp)	///< update maximum theta
						maxTheta = temp;
					LORs[index].t = theta;
					LORs[index].r = radial;
					fprintf(fileID, "heads[%d].det[%d] to heads[%d].det[%d] : %f,%f\n", i, k, indHead, l, LORs[index].r, LORs[index].t);
					index++;
				}
			}
		}
	}fclose(fileID);
	/////////////////////////////////////////////////////////////////////
	maxRadial = maxRadial / xrSamplingInterval_mm;
	/////////////////////////////////////////////////////////////////////
	//
	fileID = fopen("detectors.txt", "w");
	for (int j = 0; j < head_num; j++) {
		for (int i = 0; i < detector_num; i++) {
			fprintf(fileID, "heads[%d].det[%d] : %f,%f\n",j,i, heads[j].det[i].x, heads[j].det[i].y);
		}fprintf(fileID, "\n");
	}fclose(fileID);
	for (int i = 0; i < head_num; i++) {
		free(heads[i].det);
	}free(heads);
	/////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// assigned sinogram bin is or not
	int* sinogram = (int*)calloc(int((totalAngleViewNum)) * xrNum, sizeof(int));

	fileID = fopen("LORs.txt", "w");
	for (int i = 0; i < index; i++) {
		float temp = LORs[i].r / xrSamplingInterval_mm;
		//float temp = LORs[i].r / bin_interval;
		temp = round(temp);
		float tmpTheta = LORs[i].t;
		tmpTheta = round(tmpTheta / rtheta);
		if (int(tmpTheta) == totalAngleViewNum) 
			tmpTheta = 0;
		//if (temp <= (xrNum - 1)/2 && temp >= -(xrNum - 1)/2) {
			//int tmpRadial = temp + (xrNum - 1) / 2;
		if (temp <= limitRadial-1 && temp >= -(limitRadial-1)) {
			int tmpRadial = temp + (xrNum - 1) / 2;
			*(sinogram + xrNum*int(tmpTheta) + tmpRadial) = 1;
		}
		fprintf(fileID, "%d,%d\n", (int)temp, int(tmpTheta));
	}fclose(fileID);
	/////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// save sinogram
	//int dataSize = totalAngleViewNum * (2 * int(sqrt(2 * pow(resolution / 2, 2))) + 5)	
	int dataSize = totalAngleViewNum * xrNum;
	fileID = fopen(filename, "wb");
	fwrite(sinogram, sizeof(int), dataSize, fileID);
	fclose(fileID);
	/////////////////////////////////////////////////////////////////////

	free(LORs); free(sinogram);

	printf("Head to Head distance : %f mm\n", headTohead);
	printf("Head size : %f mm\n", head_size);
	printf("rtheta : %f\n", rtheta);
}


void gap_sino(int head_num, float detector_width, float xrSampling_mm, int detector_num, float dis_head, char* filename)
{
	int totalDetectorNum = 0;
	float rtheta = 0;
	float imageWidth = round(sqrt(2 * pow(dis_head / 2.f, 2))/xrSampling_mm - 0.5)*xrSampling_mm;
	imageWidth = round((imageWidth / xrSampling_mm) / 2. - 0.5)*2.;
	// In Matlab , int xrNum = 2 * round(sqrt(2 * pow(imageWidth - round(((imageWidth - 1) / 2.)-0.5) - 1, 2)) + 0.5) + 3;
	int xrNum = 2 * round(sqrt(2 * pow(imageWidth - round(((imageWidth - 1) / 2.)-0.5) - 1, 2)) + 0.5) + 3;
	printf("# of radial element : %d\n", xrNum);
	int limitRadial = imageWidth / 2;

	float head_size = detector_num*detector_width;	///< calculate a head size according to detector number and width
	float gap_angle = 360./head_num-2*atan(head_size/dis_head)*180./PI;
	float detector_interval = detector_width;
	float xrSamplingInterval_mm = xrSampling_mm;


	totalDetectorNum = detector_num*head_num;
	
	rtheta = 180.f / (detector_num*head_num/2);
	int totalAngleViewNum = num_yr(detector_num, head_num);
	printf("# of angle view : %d\n", totalAngleViewNum);

	FILE* fileID;	///< variable for save file 
	polPoint* LORs = (polPoint*)calloc(detector_num*detector_num*(head_num - 3)*head_num, sizeof(polPoint));	///< variable to save LOR's polar coordinate 
	head* heads = (head*)calloc(head_num, sizeof(head));	///< variable to save heads 
	for (int i = 0; i < head_num; i++) {
		heads[i].det = (carPoint*)calloc(detector_num, sizeof(carPoint));	///< variable to save totalDetectorNum cartesian coordinate
	}

	/////////////////////////////////////////////////////////////////////
	/// collocation detection	
	for (int i = 0; i < detector_num; i++) {
		heads[0].det[i].x = 0 + (detector_interval / 2.) + i*detector_interval - head_size / 2.;
		heads[0].det[i].y = dis_head / 2.;
	}
	for (int j = 1; j < head_num; j++) {
		for (int i = 0; i < detector_num; i++) {
			float rotAngle = 360. / head_num;
			heads[j].det[i] = rotClock(heads[j - 1].det[i], rotAngle);
		}
	}
	/////////////////////////////////////////////////////////////////////
	fileID = fopen("detector_LORs.txt", "w");
	/////////////////////////////////////////////////////////////////////
	// calculate LORs
	int index = 0;	///< variable for LORs number index
	float maxRadial = 0.;	///< to check maximum radial distance
	float maxTheta = 0.;	///< to check maximum theta angle
	for (int i = 0; i < head_num; i++) {
		for (int j = 0; j < head_num - 3; j++) {
			int indHead = i + j + 2;
			if (indHead >= head_num)	indHead = indHead - head_num;
			for (int k = 0; k < detector_num; k++) {
				for (int l = 0; l < detector_num; l++) {
					float gradient = (heads[i].det[k].y - heads[indHead].det[l].y)
						/ (heads[i].det[k].x - heads[indHead].det[l].x);
					float radial = (-gradient*heads[i].det[k].x + heads[i].det[k].y)
						/ sqrt(pow(gradient, 2) + 1);
					float theta = radianTodegree(atan(gradient)) >= 0 ? radianTodegree(atan(gradient)) : radianTodegree(atan(gradient)) + 180;
					float temp = radial;
					if (maxRadial < temp)	///< update maximum radial	
						maxRadial = temp;
					temp = theta;
					if (maxTheta < temp)	///< update maximum theta
						maxTheta = temp;
					LORs[index].t = theta;
					LORs[index].r = radial;
					fprintf(fileID, "heads[%d].det[%d] to heads[%d].det[%d] : %f,%f\n", i, k, indHead, l, LORs[index].r, LORs[index].t);
					index++;
				}
			}
		}
	}fclose(fileID);
	/////////////////////////////////////////////////////////////////////
	maxRadial = maxRadial / xrSamplingInterval_mm;
	/////////////////////////////////////////////////////////////////////
	//
	fileID = fopen("detectors.txt", "w");
	for (int j = 0; j < head_num; j++) {
		for (int i = 0; i < detector_num; i++) {
			fprintf(fileID, "heads[%d].det[%d] : %f,%f\n", j, i, heads[j].det[i].x, heads[j].det[i].y);
		}fprintf(fileID, "\n");
	}fclose(fileID);
	for (int i = 0; i < head_num; i++) {
		free(heads[i].det);
	}free(heads);
	/////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// assigned sinogram bin is or not
	int* sinogram = (int*)calloc(int((totalAngleViewNum)) * xrNum, sizeof(int));

	fileID = fopen("LORs.txt", "w");
	for (int i = 0; i < index; i++) {
		float temp = LORs[i].r / xrSamplingInterval_mm;
		//float temp = LORs[i].r / bin_interval;
		temp = round(temp);
		float tmpTheta = LORs[i].t;
		tmpTheta = round(tmpTheta / rtheta);
		if (int(tmpTheta) == totalAngleViewNum)
			tmpTheta = 0;
		//if (temp <= (xrNum - 1)/2 && temp >= -(xrNum - 1)/2) {
		//int tmpRadial = temp + (xrNum - 1) / 2;
		/*
		if (temp <= limitRadial - 1 && temp >= -(limitRadial - 1)) {
			int tmpRadial = temp + (xrNum - 1) / 2;
			*(sinogram + xrNum*int(tmpTheta) + tmpRadial) = 1;
		}*/
		int tmpRadial = temp + round(xrNum / 2 +0.5);
		*(sinogram + xrNum*int(tmpTheta) + tmpRadial) = 1;
		fprintf(fileID, "%d,%d\n", (int)temp, int(tmpTheta));
	}fclose(fileID);
	/////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////
	// save sinogram
	//int dataSize = totalAngleViewNum * (2 * int(sqrt(2 * pow(resolution / 2, 2))) + 5)	
	int dataSize = totalAngleViewNum * xrNum;
	fileID = fopen(filename, "wb");
	fwrite(sinogram, sizeof(int), dataSize, fileID);
	fclose(fileID);
	/////////////////////////////////////////////////////////////////////

	free(LORs); free(sinogram);

	printf("Head to Head distance : %f mm\n", dis_head);
	printf("Head size : %f mm\n", head_size);
	printf("rtheta : %f\n", rtheta);
}

int num_yr(int num_detecter, int num_head)
{
	float yr = 180. / (num_detecter*num_head / 2.);
	int count = 0;
	
	while (count*yr <= 179) {
		count++;
	}
	return count;
}