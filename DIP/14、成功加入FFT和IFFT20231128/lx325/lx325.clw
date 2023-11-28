; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLx325View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "lx325.h"
LastPage=0

ClassCount=6
Class1=CLx325App
Class2=CLx325Doc
Class3=CLx325View
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CHistogramDlg
Resource3=IDD_DIALOG1

[CLS:CLx325App]
Type=0
HeaderFile=lx325.h
ImplementationFile=lx325.cpp
Filter=N
LastObject=CLx325App

[CLS:CLx325Doc]
Type=0
HeaderFile=lx325Doc.h
ImplementationFile=lx325Doc.cpp
Filter=N
LastObject=CLx325Doc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CLx325View]
Type=0
HeaderFile=lx325View.h
ImplementationFile=lx325View.cpp
Filter=C
LastObject=ID_EQUALIZE
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_IFFT




[CLS:CAboutDlg]
Type=0
HeaderFile=lx325.cpp
ImplementationFile=lx325.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_FILE_PRINT
Command7=ID_APP_ABOUT
Command8=ID_GRAY
Command9=ID_HISTOGRAMDLG
Command10=ID_LINETRANS
Command11=ID_EQUALIZE
Command12=ID_FT
Command13=ID_IFT
Command14=ID_FFT
Command15=ID_IFFT
CommandCount=15

[DLG:IDD_DIALOG1]
Type=1
Class=CHistogramDlg
ControlCount=0

[CLS:CHistogramDlg]
Type=0
HeaderFile=HistogramDlg.h
ImplementationFile=HistogramDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CHistogramDlg
VirtualFilter=dWC

