#include "stdafx.h"


void CSkeletonBasics::delimited_output(std::string delimiter, std::string filename){
	std::string outputFile;
	time_t currenttime = time(NULL);
	char* timestring = ctime(&currenttime);
	outputFile = filename;
	std::string conv(timestring);
	conv = conv.substr(0, conv.length() - 1);

	for (int i = 0; i < conv.length(); i++){
		if (conv[i] == ':' || conv[i] == ' '){
			conv[i] = '_';
		}
	}

	outputFile += conv;

	outputFile += ".txt";
	CSkeletonBasics::fout.open(outputFile);
	//End elaborate date and time filename setup

	fout << "HIP_CENTER" << ',' << ',' << ',';
	fout << "SPINE" << ',' << ',' << ',';
	fout << "SHOULDER_CENTER" << ',' << ',' << ',';
	fout << "HEAD" << ',' << ',' << ',';
	fout << "SHOULDER_LEFT" << ',' << ',' << ',';
	fout << "ELBOW_LEFT" << ',' << ',' << ',';
	fout << "WRIST_LEFT" << ',' << ',' << ',';
	fout << "HAND_LEFT" << ',' << ',' << ',';
	fout << "SHOULDER_RIGHT" << ',' << ',' << ',';
	fout << "ELBOW_RIGHT" << ',' << ',' << ',';
	fout << "WRIST_RIGHT" << ',' << ',' << ',';
	fout << "HAND_RIGHT" << ',' << ',' << ',';
	fout << "HIP_LEFT" << ',' << ',' << ',';
	fout << "KNEE_LEFT" << ',' << ',' << ',';
	fout << "ANKLE_LEFT" << ',' << ',' << ',';
	fout << "FOOT_LEFT" << ',' << ',' << ',';
	fout << "HIP_RIGHT" << ',' << ',' << ',';
	fout << "KNEE_RIGHT" << ',' << ',' << ',';
	fout << "ANKLE_RIGHT" << ',' << ',' << ',';
	fout << "FOOT_RIGHT" << ',' << ',' << ',';

	fout << "NECK_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "TORSO_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "RIGHT_UPPER_ARM_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "RIGHT_LOWER_ARM_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "LEFT_UPPER_ARM_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "LEFT_LOWER_ARM_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "RIGHT_UPPER_LEG_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "RIGHT_LOWER_LEG_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "LEFT_UPPER_LEG_CENTER_OF_MASS" << ',' << ',' << ',';
	fout << "LEFT_LOWER_LEG_CENTER_OF_MASS" << ',' << ',' << ',';

	fout << "NECK_ENERGY" << ',' << ',' << ',';
	fout << "TORSO_ENERGY" << ',' << ',' << ',';
	fout << "RIGHT_UPPER_ARM_ENERGY" << ',' << ',' << ',';
	fout << "RIGHT_LOWER_ARM_ENERGY" << ',' << ',' << ',';
	fout << "LEFT_UPPER_ARM_ENERGY" << ',' << ',' << ',';
	fout << "LEFT_LOWER_ARM_ENERGY" << ',' << ',' << ',';
	fout << "RIGHT_UPPER_LEG_ENERGY" << ',' << ',' << ',';
	fout << "RIGHT_LOWER_LEG_ENERGY" << ',' << ',' << ',';
	fout << "LEFT_UPPER_LEG_ENERGY" << ',' << ',' << ',';
	fout << "LEFT_LOWER_LEG_ENERGY" << ',' << ',' << ',';
	fout << "COMBINED_ENERGY" << ',';
	fout << "TOTAL_ENERGY" << ',';

	fout << std::endl;

	for (int p = 0; p < 39; p++){
		fout << 'x' << ',' << 'y' << ',' << 'z' << ',';
	}

	fout << std::endl;

	fout.close();
}

void CSkeletonBasics::COM_output(std::string filename){
	std::string outputFile;
	time_t currenttime = time(NULL);
	char* timestring = ctime(&currenttime);
	outputFile = filename;
	std::string conv(timestring);
	conv = conv.substr(0, conv.length() - 1);

	for (int i = 0; i < conv.length(); i++){
		if (conv[i] == ':' || conv[i] == ' '){
			conv[i] = '_';
		}
	}

	outputFile += conv;

	outputFile += ".csv";
	fout.open(outputFile);


	fout << "HIP_CENTER" << ',' << ',' << ',';
	fout << "SPINE" << ',' << ',' << ',';
	fout << "SHOULDER_CENTER" << ',' << ',' << ',';
	fout << "HEAD" << ',' << ',' << ',';
	fout << "SHOULDER_LEFT" << ',' << ',' << ',';
	fout << "ELBOW_LEFT" << ',' << ',' << ',';
	fout << "WRIST_LEFT" << ',' << ',' << ',';
	fout << "HAND_LEFT" << ',' << ',' << ',';
	fout << "SHOULDER_RIGHT" << ',' << ',' << ',';
	fout << "ELBOW_RIGHT" << ',' << ',' << ',';
	fout << "WRIST_RIGHT" << ',' << ',' << ',';
	fout << "HAND_RIGHT" << ',' << ',' << ',';
	fout << "HIP_LEFT" << ',' << ',' << ',';
	fout << "KNEE_LEFT" << ',' << ',' << ',';
	fout << "ANKLE_LEFT" << ',' << ',' << ',';
	fout << "FOOT_LEFT" << ',' << ',' << ',';
	fout << "HIP_RIGHT" << ',' << ',' << ',';
	fout << "KNEE_RIGHT" << ',' << ',' << ',';
	fout << "ANKLE_RIGHT" << ',' << ',' << ',';
	fout << "FOOT_RIGHT" << ',' << ',' << ',';

	fout << "NECK CoM" << ',' << ',' << ',';
	fout << "TORSO_CoM" << ',' << ',' << ',';
	fout << "RIGHT_UPPER_ARM_CoM" << ',' << ',' << ',';
	fout << "RIGHT_LOWER_ARM_CoM" << ',' << ',' << ',';
	fout << "LEFT_UPPER_ARM_CoM" << ',' << ',' << ',';
	fout << "LEFT_LOWER_ARM_CoM" << ',' << ',' << ',';
	fout << "RIGHT_UPPER_LEG_CoM" << ',' << ',' << ',';
	fout << "RIGHT_LOWER_LEG_CoM" << ',' << ',' << ',';
	fout << "LEFT_UPPER_LEG_CoM" << ',' << ',' << ',';
	fout << "LEFT_LOWER_LEG_CoM" << ',' << ',' << ',';

	fout << std::endl;
	for (int a = 0; a < 30; a++){
		fout << 'x' << ',' << 'y' << ',' << 'z' << ',';
	}

	fout << "Neck" << ',';
	fout << "Torso" << ',';
	fout << "Right_Upper_Arm" << ',';
	fout << "Right_Lower_Arm" << ',';
	fout << "Left_Upper_Arm" << ',';
	fout << "Left_Lower_Arm" << ',';
	fout << "Right_Upper_Leg" << ',';
	fout << "Right_Lower_Leg" << ',';
	fout << "Left_Upper_Leg" << ',';
	fout << "Left_Lower_Leg" << ',';

	fout << "Energy Expended This Frame" << ',';
	fout << "Total Energy Expended" << ',';

	fout << std::endl;

	for (int i = 0; i < coords.size() - 1; i++){

		if (i>0 && i<	(coords.size()-1))
			distanceDeviationCheck(i);

		for (int j = 0; j < coords[j].size() - 1; j++){
			fout << coords[i][j].x << ',';
			fout << coords[i][j].y << ',';
			fout << coords[i][j].z << ',';
		}

		fout << COMSES[i].NECK.x << ',';
		fout << COMSES[i].NECK.y << ',';
		fout << COMSES[i].NECK.z << ',';

		fout << COMSES[i].TORSO.x << ',';
		fout << COMSES[i].TORSO.y << ',';
		fout << COMSES[i].TORSO.z << ',';

		fout << COMSES[i].RIGHT_UPPER_ARM.x << ',';
		fout << COMSES[i].RIGHT_UPPER_ARM.y << ',';
		fout << COMSES[i].RIGHT_UPPER_ARM.z << ',';

		fout << COMSES[i].RIGHT_LOWER_ARM.x << ',';
		fout << COMSES[i].RIGHT_LOWER_ARM.y << ',';
		fout << COMSES[i].RIGHT_LOWER_ARM.z << ',';

		fout << COMSES[i].LEFT_UPPER_ARM.x << ',';
		fout << COMSES[i].LEFT_UPPER_ARM.y << ',';
		fout << COMSES[i].LEFT_UPPER_ARM.z << ',';

		fout << COMSES[i].LEFT_LOWER_ARM.x << ',';
		fout << COMSES[i].LEFT_LOWER_ARM.y << ',';
		fout << COMSES[i].LEFT_LOWER_ARM.z << ',';

		fout << COMSES[i].RIGHT_UPPER_LEG.x << ',';
		fout << COMSES[i].RIGHT_UPPER_LEG.y << ',';
		fout << COMSES[i].RIGHT_UPPER_LEG.z << ',';

		fout << COMSES[i].RIGHT_LOWER_LEG.x << ',';
		fout << COMSES[i].RIGHT_LOWER_LEG.y << ',';
		fout << COMSES[i].RIGHT_LOWER_LEG.z << ',';

		fout << COMSES[i].LEFT_UPPER_LEG.x << ',';
		fout << COMSES[i].LEFT_UPPER_LEG.y << ',';
		fout << COMSES[i].LEFT_UPPER_LEG.z << ',';

		fout << COMSES[i].LEFT_LOWER_LEG.x << ',';
		fout << COMSES[i].LEFT_LOWER_LEG.y << ',';
		fout << COMSES[i].LEFT_LOWER_LEG.z << ',';

		fout << energyskels[i].NECK_ENERGY << ',';
		fout << energyskels[i].TORSO_ENERGY << ',';
		fout << energyskels[i].RIGHT_UPPER_ARM_ENERGY << ',';
		fout << energyskels[i].RIGHT_LOWER_ARM_ENERGY << ',';
		fout << energyskels[i].LEFT_UPPER_ARM_ENERGY << ',';
		fout << energyskels[i].LEFT_LOWER_ARM_ENERGY << ',';
		fout << energyskels[i].RIGHT_UPPER_LEG_ENERGY << ',';
		fout << energyskels[i].RIGHT_LOWER_LEG_ENERGY << ',';
		fout << energyskels[i].LEFT_UPPER_LEG_ENERGY << ',';
		fout << energyskels[i].LEFT_LOWER_LEG_ENERGY << ',';

		fout << Energy(energyskels[i]) << ',';
		fout << currentTotalEnergyExpended[i] << ',';

		fout << std::endl;
	}

	fout << std::endl;
}

void CSkeletonBasics::playback_output(std::string filename){
	std::string outputFile;
	time_t currenttime = time(NULL);
	char* timestring = ctime(&currenttime);
	outputFile = filename;
	std::string conv(timestring);
	conv = conv.substr(0, conv.length() - 1);

	for (int i = 0; i < conv.length(); i++){
		if (conv[i] == ':' || conv[i] == ' '){
			conv[i] = '_';
		}
	}

	outputFile += conv;

	outputFile += ".txt";
	CSkeletonBasics::fout.open(outputFile);
	for (int i = 0; i < coords.size() - 1; i++){
		for (int j = 0; j < coords[i].size() - 1; j++){
			fout << coords[i][j].x << std::endl;
			fout << coords[i][j].y << std::endl;
			fout << coords[i][j].z << std::endl;
		}
	}
}
