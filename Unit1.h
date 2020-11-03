//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Jpeg.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TStatusBar *StatusBar1;
	TImage *Image1;
	TActionList *ActionList1;
	TImageList *ImageList1;
	TFileListBox *FileListBox1;
	TFilterComboBox *FilterComboBox1;
	TDirectoryListBox *DirectoryListBox1;
	TDriveComboBox *DriveComboBox1;
	TMenuItem *Plik1;
	TMenuItem *Nowy1;
	TMenuItem *Otworz1;
	TMenuItem *Zapisz1;
	TMenuItem *Zapiszjako1;
	TMenuItem *Zakoncz1;
	TMenuItem *Narzedzia1;
	TMenuItem *Obrtwlewo1;
	TMenuItem *Obrtwprawo1;
	TMenuItem *Skalowanie1;
	TAction *acNowy;
	TAction *acOtworz;
	TAction *acZapisz;
	TAction *acObrotWLewo;
	TAction *acObrotWPrawo;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TAction *acWyjdz;
	TSplitter *Splitter1;
	TProgressBar *ProgressBar1;
	TAction *acPelnyEkran;
	TOpenPictureDialog *OpenPictureDialog1;
	TSavePictureDialog *SavePictureDialog1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall acOtworzExecute(TObject *Sender);
	void __fastcall acZapiszExecute(TObject *Sender);
	void __fastcall acObrotWLewoExecute(TObject *Sender);
	void __fastcall acObrotWPrawoExecute(TObject *Sender);
	void __fastcall acPelnyEkranExecute(TObject *Sender);
	void __fastcall acNowyExecute(TObject *Sender);
	void __fastcall FileListBox1DblClick(TObject *Sender);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall acWyjdzExecute(TObject *Sender);
	void __fastcall Zapiszjako1Click(TObject *Sender);




private:	// User declarations
	TJPEGImage *JPEGImage1;
	Graphics::TBitmap *bitmap1;
	void pokazObraz();
	void save();
	bool zmodyfikowany;
	TRect lastRect;
	TRect sourceRect;
	TPoint mousePos;


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
