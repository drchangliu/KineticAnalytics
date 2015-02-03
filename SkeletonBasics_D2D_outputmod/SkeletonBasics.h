//------------------------------------------------------------------------------
// <copyright file="SkeletonBasics.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "resource.h"
#include "NuiApi.h"
#include <fstream>
#include <vector>
#include <ctime>
struct coord{
	double x;
	double y;
	double z;

};
struct COM{
	coord NECK; //Head to shoulder center
	coord TORSO; //shoulder center to hip center
	coord RIGHT_UPPER_ARM; //shoulder right to elbow right
	coord RIGHT_LOWER_ARM; //elbow right to wrist right
	coord LEFT_UPPER_ARM; //shoulder left to elbow left
	coord LEFT_LOWER_ARM; //elbow left to wrist left
	coord RIGHT_UPPER_LEG; //Hip right to knee right
	coord RIGHT_LOWER_LEG; // Knee  right to ankle right
	coord LEFT_UPPER_LEG; //Hip left to knee left
	coord LEFT_LOWER_LEG; //Knee left to ankle left

};

struct EnergySkeleton
{
    double           NECK_ENERGY;
    double          TORSO_ENERGY;
    double RIGHT_UPPER_ARM_ENERGY;
	double RIGHT_LOWER_ARM_ENERGY;
	double LEFT_UPPER_ARM_ENERGY;
	double LEFT_LOWER_ARM_ENERGY;
	double RIGHT_UPPER_LEG_ENERGY;
	double RIGHT_LOWER_LEG_ENERGY;
	double LEFT_UPPER_LEG_ENERGY;
	double LEFT_LOWER_LEG_ENERGY;

};
class CSkeletonBasics
{
    static const int        cScreenWidth  = 320;
    static const int        cScreenHeight = 240;

    static const int        cStatusMessageMaxLen = MAX_PATH*2;

public:
    /// <summary>
    /// Constructor
    /// </summary>
    CSkeletonBasics();

    /// <summary>
    /// Destructor
    /// </summary>
    ~CSkeletonBasics();

    /// <summary>
    /// Handles window messages, passes most to the class instance to handle
    /// </summary>
    /// <param name="hWnd">window message is for</param>
    /// <param name="uMsg">message</param>
    /// <param name="wParam">message data</param>
    /// <param name="lParam">additional message data</param>
    /// <returns>result of message processing</returns>
    static LRESULT CALLBACK MessageRouter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    /// <summary>
    /// Handle windows messages for a class instance
    /// </summary>
    /// <param name="hWnd">window message is for</param>
    /// <param name="uMsg">message</param>
    /// <param name="wParam">message data</param>
    /// <param name="lParam">additional message data</param>
    /// <returns>result of message processing</returns>
    LRESULT CALLBACK        DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    /// <summary>
    /// Creates the main window and begins processing
    /// </summary>
    /// <param name="hInstance"></param>
    /// <param name="nCmdShow"></param>
    int                     Run(HINSTANCE hInstance, int nCmdShow);

private:
	std::ofstream fout;
	size_t frame_count;
	int test;
	std::vector<std::vector<coord> > coords;
	std::vector<COM> COMSES;
    std::vector<EnergySkeleton> energyskels;
    std::vector<double> currentTotalEnergyExpended;

	bool recording;
	double weight;
	double FINAL_ENERGY;
	void original_output(std::string filename);
	void delimited_output(std::string delimiter, std::string filename);
	void playback_output(std::string filename);
	void COM_output(std::string filename);
	void new_main_out();
	double distance(double x1, double x2, double y1, double y2, double z1, double z2);
	double Energy(EnergySkeleton en);
    EnergySkeleton EnergyPartials(COM com1, COM com2);

	//double singleEnergy()
	double velocity(coord coord1, coord coord2); //returns the distance betweent the points divide by 30, our constant time interval; V= deltaP/T
	COM calculate_COM(NUI_SKELETON_DATA skeleton); //calculates the center of mass values for all points on the skelelton and returns them in a struct
	coord calculate_single_COM(float x1, float y1, float z1, float x2, float y2, float z2, double percent); //percent is the fractional distance. 0.5 would be the midpoint.
    HWND                    m_hWnd;

    bool                    m_bSeatedMode;

    // Current Kinect
    INuiSensor*             m_pNuiSensor;

    // Skeletal drawing
    ID2D1HwndRenderTarget*   m_pRenderTarget;
    ID2D1SolidColorBrush*    m_pBrushJointTracked;
    ID2D1SolidColorBrush*    m_pBrushJointInferred;
    ID2D1SolidColorBrush*    m_pBrushBoneTracked;
    ID2D1SolidColorBrush*    m_pBrushBoneInferred;
    D2D1_POINT_2F            m_Points[NUI_SKELETON_POSITION_COUNT];

    // Direct2D
    ID2D1Factory*           m_pD2DFactory;

    HANDLE                  m_pSkeletonStreamHandle;
    HANDLE                  m_hNextSkeletonEvent;

    /// <summary>
    /// Main processing function
    /// </summary>
    void                    Update();

    /// <summary>
    /// Create the first connected Kinect found
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code</returns>
    HRESULT                 CreateFirstConnected();

    /// <summary>
    /// Handle new skeleton data
    /// </summary>
    void                    ProcessSkeleton();

    /// <summary>
    /// Ensure necessary Direct2d resources are created
    /// </summary>
    /// <returns>S_OK if successful, otherwise an error code</returns>
    HRESULT                 EnsureDirect2DResources( );

    /// <summary>
    /// Dispose Direct2d resources
    /// </summary>
    void                    DiscardDirect2DResources( );

    /// <summary>
    /// Draws a bone line between two joints
    /// </summary>
    /// <param name="skel">skeleton to draw bones from</param>
    /// <param name="joint0">joint to start drawing from</param>
    /// <param name="joint1">joint to end drawing at</param>
    void                    DrawBone(const NUI_SKELETON_DATA & skel, NUI_SKELETON_POSITION_INDEX bone0, NUI_SKELETON_POSITION_INDEX bone1);

    /// <summary>
    /// Draws a skeleton
    /// </summary>
    /// <param name="skel">skeleton to draw</param>
    /// <param name="windowWidth">width (in pixels) of output buffer</param>
    /// <param name="windowHeight">height (in pixels) of output buffer</param>
    void                    DrawSkeleton(const NUI_SKELETON_DATA & skel, int windowWidth, int windowHeight);

    /// <summary>
    /// Converts a skeleton point to screen space
    /// </summary>
    /// <param name="skeletonPoint">skeleton point to tranform</param>
    /// <param name="width">width (in pixels) of output buffer</param>
    /// <param name="height">height (in pixels) of output buffer</param>
    /// <returns>point in screen-space</returns>
    D2D1_POINT_2F           SkeletonToScreen(Vector4 skeletonPoint, int width, int height);


    /// <summary>
    /// Set the status bar message
    /// </summary>
    /// <param name="szMessage">message to display</param>
    void                    SetStatusMessage(WCHAR* szMessage);
};
