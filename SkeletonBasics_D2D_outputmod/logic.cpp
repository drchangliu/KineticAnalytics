#include "stdafx.h"
#include "SkeletonBasics.h"

void CSkeletonBasics::distanceDeviationCheck(int currentFrame)
{
    for (int currentJoint = 0; currentJoint < coords[currentFrame].size(); currentJoint++)
    {
        if ((abs(coords[currentFrame][currentJoint].x - coords[currentFrame - 1][currentJoint].x))
                + (abs(coords[currentFrame][currentJoint].y - coords[currentFrame - 1][currentJoint].y))
                + (abs(coords[currentFrame][currentJoint].z - coords[currentFrame - 1][currentJoint].z)) > 2)
        {

            recursiveCaseDistanceDeviationCheck(currentFrame, currentJoint);
        }
    }

}

void CSkeletonBasics::recursiveCaseDistanceDeviationCheck(int currentFrame, int currentJoint)
{
    int findNextValidFrame = 1;
    while (((abs(coords[currentFrame + findNextValidFrame][currentJoint].x - coords[currentFrame - 1][currentJoint].x))
            +   (abs(coords[currentFrame + findNextValidFrame][currentJoint].y - coords[currentFrame - 1][currentJoint].y))
            +   (abs(coords[currentFrame + findNextValidFrame][currentJoint].z - coords[currentFrame - 1][currentJoint].z))
            > 2) && findNextValidFrame < (coords.size() - 1))
    {
        findNextValidFrame++;
    }

    for (int i = 0; i < findNextValidFrame; i++)
    {

        coords[currentFrame + i][currentJoint].x =
            (coords[currentFrame - 1][currentJoint].x * (- i + findNextValidFrame)
             + (coords[currentFrame + findNextValidFrame][currentJoint].x) * findNextValidFrame) / (2* findNextValidFrame);
        coords[currentFrame + i][currentJoint].y =
            (coords[currentFrame - 1][currentJoint].y * (-i + findNextValidFrame)
             + (coords[currentFrame + findNextValidFrame][currentJoint].y) * findNextValidFrame) / (2 * findNextValidFrame);
        coords[currentFrame + i][currentJoint].z =
            (coords[currentFrame - 1][currentJoint].z * (-i + findNextValidFrame)
             + (coords[currentFrame + findNextValidFrame][currentJoint].z) * findNextValidFrame) / (2 * findNextValidFrame);
    }

}

void CSkeletonBasics::reduceJitter(int currentFrame, int currentJoint)
{
    if (isJittering(currentFrame, currentJoint))
    {
        coords[currentFrame][currentJoint] = normalizeJitter(currentFrame,currentJoint);
    }
}

bool CSkeletonBasics::isJittering(int currentFrame, int currentJoint)
{
    if((coords.size()-30)<currentFrame)
        return false;

    bool knownGreenPoint = true;
    positionPerSecond.push_back(coords[currentFrame][currentJoint]);
    coord averageOfCurrent;

    std::vector<coord> positionPerSecond;
    for(int i=1; i<30; i++)
    {
        positionPerSecond.push_back(coords[currentFrame+i][currentJoint]);

        knownGreenPoint = isJointOrScreenEdgeCollision(currentFrame + i, currentJoint);

        if(knownGreenPoint==false)
        {
            for(int j=0; j<positionPerSecond.size(); j++)
            {
                averageOfCurrent.x+=coords[currentFrame+j][currentJoint].x;
                averageOfCurrent.y+=coords[currentFrame+j][currentJoint].y;
                averageOfCurrent.z+=coords[currentFrame+j][currentJoint].z;
            }
            averageOfCurrent.x /= positionPerSecond.size();
            averageOfCurrent.y /= positionPerSecond.size();
            averageOfCurrent.z /= positionPerSecond.size();
            coords[currentFrame+i][currentJoint]=averageOfCurrent;
        }
    }


}

isJointOrScreenEdgeCollision(int currentFrame, int currentJoint)
{
    int greatestX=-0.2;
    int leastX=3;
    int greatestY=-0.2;
    int leastY=3;
    int greatestZ=-0.2;
    int leastZ=3;

    if( coords[currentFrame][currentJoint].x>greatestX ||
        coords[currentFrame][currentJoint].x<leastX    ||
        coords[currentFrame][currentJoint].y>greatestY ||
        coords[currentFrame][currentJoint].y<leastY    ||
        coords[currentFrame][currentJoint].z>greatestZ ||
        coords[currentFrame][currentJoint].z<leastZ    || )
    {
        return true;
    }

    return false;
}

coord CSkeletonBasics::normalizeJitter(int currentFrame, int currentJoint)
{
    coord normalizedMedium;
    normalizedMedium.x = normalizedMedium.y = normalizedMedium.z = 0;


    for(int i=0; i<30; i++)
    {
        normalizedMedium.x += coords[currentFrame + i][currentJoint].x;
        normalizedMedium.y += coords[currentFrame + i][currentJoint].y;
        normalizedMedium.z += coords[currentFrame + i][currentJoint].z;
    }
    normalizedMedium.x /= 30;
    normalizedMedium.y /= 30;
    normalizedMedium.z /= 30;

    return normalizedMedium;
}

double CSkeletonBasics::distance(double x1, double x2, double y1, double y2, double z1, double z2)
{
    double xsq, ysq, zsq;
    xsq = pow((x1 - x2), 2);
    ysq = pow((y1 - y2), 2);
    zsq = pow((z1 - z2), 2);
    return sqrt(xsq + ysq + zsq);
}

coord CSkeletonBasics::calculate_single_COM(float x1, float y1, float z1, float x2, float y2, float z2, double percent)
{
    coord temp;
    temp.x = (x1 + x2)*percent;
    temp.y = (y1 + y2)*percent;
    temp.z = (z1 + z2)*percent;
    return temp;

}

COM CSkeletonBasics::calculate_COM(NUI_SKELETON_DATA skeleton)
{
    COM temp;

    temp.NECK = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HEAD].x,
                                     skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HEAD].y,
                                     skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HEAD].z,
                                     skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].x,
                                     skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].y,
                                     skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].z,
                                     0.54);

    temp.TORSO = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].x,
                                      skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].y,
                                      skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_CENTER].z,
                                      skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_CENTER].x,
                                      skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_CENTER].y,
                                      skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_CENTER].z,
                                      0.46375);
    temp.RIGHT_UPPER_ARM = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_RIGHT].z,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].z,
                           0.47);
    temp.RIGHT_LOWER_ARM = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_RIGHT].z,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_RIGHT].z,
                           0.4202);
    temp.LEFT_UPPER_ARM = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_SHOULDER_LEFT].z,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].z,
                          0.47);
    temp.LEFT_LOWER_ARM = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ELBOW_LEFT].z,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_WRIST_LEFT].z,
                          0.4202);
    temp.RIGHT_UPPER_LEG = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_RIGHT].z,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_RIGHT].z,
                           0.42584);
    temp.RIGHT_LOWER_LEG = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_RIGHT].z,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_RIGHT].x,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_RIGHT].y,
                           skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_RIGHT].z,
                           0.414);
    temp.LEFT_UPPER_LEG = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HIP_LEFT].z,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_LEFT].z,
                          0.42584);
    temp.LEFT_LOWER_LEG = calculate_single_COM(skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_KNEE_LEFT].z,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_LEFT].x,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_LEFT].y,
                          skeleton.SkeletonPositions[NUI_SKELETON_POSITION_ANKLE_LEFT].z,
                          0.414);
    return temp;

}
double CSkeletonBasics::velocity(coord coord1, coord coord2)
{
    return distance(coord1.x, coord2.x, coord1.y, coord2.y, coord1.z, coord2.z) / 30.0;
}

// Here we are using the formula for kinetic energy to calculate energy expended between two frames
// The formula is KE = 0.5 * mass * velocity^2
// For the mass we use the weight of the person multiplied by the percent of the total body weight
// For the velocity we use our velocity function which calculates distance traveled per frame
EnergySkeleton CSkeletonBasics::EnergyPartials(COM com1, COM com2)
{
    EnergySkeleton temp_energy;
    temp_energy.NECK_ENERGY = 0.5* (weight*0.07802)*pow(velocity(com1.NECK, com2.NECK), 2); //0.07802 is the percent total body weight of the neck
    temp_energy.TORSO_ENERGY = 0.5* (weight*0.49216)*pow(velocity(com1.TORSO, com2.TORSO), 2);//0.49216 is the percent total body weight of the torso
    temp_energy.RIGHT_UPPER_ARM_ENERGY = 0.5* (weight*0.0286)*pow(velocity(com1.RIGHT_UPPER_ARM, com2.RIGHT_UPPER_ARM), 2);//0.0286 is the percent total body weight of the Upper Arm
    temp_energy.RIGHT_LOWER_ARM_ENERGY = 0.5* (weight*0.0166)*pow(velocity(com1.RIGHT_LOWER_ARM, com2.RIGHT_LOWER_ARM), 2);//0.0166 is the percent total body weight of the Lower Arm
    temp_energy.LEFT_UPPER_ARM_ENERGY = 0.5* (weight*0.0286)*pow(velocity(com1.LEFT_UPPER_ARM, com2.LEFT_UPPER_ARM), 2);//0.0286 is the percent total body weight of the Upper Arm
    temp_energy.LEFT_LOWER_ARM_ENERGY = 0.5* (weight*0.0166)*pow(velocity(com1.LEFT_LOWER_ARM, com2.LEFT_LOWER_ARM), 2);//0.0166 is the percent total body weight of the Lower Arm
    temp_energy.RIGHT_UPPER_LEG_ENERGY = 0.5* (weight*0.1056)*pow(velocity(com1.RIGHT_UPPER_LEG, com2.RIGHT_UPPER_LEG), 2);//0.1056 is the percent total body weight of the Upper Leg
    temp_energy.RIGHT_LOWER_LEG_ENERGY = 0.5* (weight*0.04725)*pow(velocity(com1.RIGHT_LOWER_LEG, com2.RIGHT_LOWER_LEG), 2);//0.04725 is the percent total body weight of the Lower Leg
    temp_energy.LEFT_UPPER_LEG_ENERGY = 0.5* (weight*0.1056)*pow(velocity(com1.LEFT_UPPER_LEG, com2.LEFT_UPPER_LEG), 2);//0.1056 is the percent total body weight of the Upper Leg
    temp_energy.LEFT_LOWER_LEG_ENERGY = 0.5* (weight*0.04725)*pow(velocity(com1.LEFT_LOWER_LEG, com2.LEFT_LOWER_LEG), 2);//0.04725 is the percent total body weight of the Lower Leg
    return temp_energy;
}

double CSkeletonBasics::Energy(EnergySkeleton en)
{
    double temp = en.NECK_ENERGY +
                  en.TORSO_ENERGY +
                  en.RIGHT_UPPER_ARM_ENERGY +
                  en.RIGHT_LOWER_ARM_ENERGY +
                  en.LEFT_UPPER_ARM_ENERGY +
                  en.LEFT_LOWER_ARM_ENERGY +
                  en.RIGHT_UPPER_LEG_ENERGY +
                  en.RIGHT_LOWER_LEG_ENERGY +
                  en.LEFT_UPPER_LEG_ENERGY +
                  en.LEFT_LOWER_LEG_ENERGY;
    return temp;
}
