/**
 * @file MainFrame.cpp
 * @author Charles B. Owen
 */
#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>
#include "MainFrame.h"
#include "ViewEdit.h"
#include "ViewTimeline.h"
#include "Picture.h"
#include "PictureFactory.h"
#include "MachineDrawable.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory path containing resources
 */
MainFrame::MainFrame(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{

}

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");
#ifdef WIN32
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    auto sizer = new wxBoxSizer(wxVERTICAL);

    auto imagesDir = mResourcesDir + ImagesDirectory;

    mViewEdit = new ViewEdit(this);
    mViewTimeline = new ViewTimeline(this, imagesDir);

    sizer->Add(mViewEdit, 1, wxEXPAND | wxALL);
    sizer->Add(mViewTimeline, 0, wxEXPAND | wxALL);

    SetSizer(sizer);
    Layout();

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    // Create Machine System's
    auto machineDrawableOne = std::make_shared<MachineDrawable>(L"One", mResourcesDir, this);
    auto machineDrawableTwo = std::make_shared<MachineDrawable>(L"Two", mResourcesDir, this);

    //
    // Create the picture
    //
    PictureFactory factory(mResourcesDir);
    factory.AddMachine(machineDrawableOne, wxPoint(800, 600));
    factory.AddMachine(machineDrawableTwo, wxPoint(2000, 600));
    mPicture = factory.AddActors();

    // Add Reference in picture
    mPicture->SetMachineOne(machineDrawableOne);
    mPicture->SetMachineTwo(machineDrawableTwo);

    // Tell the views about the picture
    mViewEdit->SetPicture(mPicture);
    mViewTimeline->SetPicture(mPicture);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

/**
 * Application about box menu handler
 * @param event The menu command event
 */
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxDialog aboutDlg;
    wxXmlResource::Get()->LoadDialog(&aboutDlg, this, L"AboutDialog");
    aboutDlg.ShowModal();
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent &event)
{
    mViewTimeline->Stop();
    Destroy();
}
