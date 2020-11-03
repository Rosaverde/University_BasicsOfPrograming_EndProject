//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TPoint imgTopLeft;
String srcFileName;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	imgTopLeft.x = Image1->ClientRect.Left;
	imgTopLeft.y = Image1->ClientRect.Bottom;

	acNowyExecute(Sender);

	JPEGImage1 = new TJPEGImage;
	ProgressBar1->Parent = StatusBar1;

	ProgressBar1->Left = 3;
	ProgressBar1->Top  = 3;
	ProgressBar1->Position = 0;
	zmodyfikowany = false;

	acObrotWLewo->Enabled = false;
	acObrotWPrawo->Enabled = false;
	acPelnyEkran->Enabled = false;
}
//---------------------------------------------------------------------------

void TForm1::pokazObraz()
{
	if(!JPEGImage1->Empty)
	{
		Image1->Canvas->Rectangle(0,0, Image1->Width, Image1->Height);
		Image1->Canvas->Draw(0, 0, JPEGImage1);

		acObrotWLewo->Enabled = true;
		acObrotWPrawo->Enabled = true;
		acPelnyEkran->Enabled = true;
	}
	else
	{
		acObrotWLewo->Enabled = false;
		acObrotWPrawo->Enabled = false;
		acPelnyEkran->Enabled = false;
	}
}
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	delete(this->JPEGImage1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::acOtworzExecute(TObject *Sender)
{
	if(OpenPictureDialog1->Execute())
	{
		srcFileName = OpenPictureDialog1->FileName;
		JPEGImage1->LoadFromFile(srcFileName);
		pokazObraz();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::acNowyExecute(TObject *Sender)
{
	// Nowa karta

	   this->Image1->Align = alClient;
}
//---------------------------------------------------------------------------

void TForm1::save()
{
	zmodyfikowany = false;
	JPEGImage1->SaveToFile(srcFileName);
}

void __fastcall TForm1::acZapiszExecute(TObject *Sender)
{
 // Zapisz
 if(srcFileName.IsEmpty())
 {
	return;
 }

 int mb_return;

 if(zmodyfikowany)
	{
		mb_return = Application->MessageBox(L"Czy chcesz zapisaæ zmiany do pliku?", L"Zapisz zmiany", MB_YESNOCANCEL | MB_ICONQUESTION);
		if(mb_return == ID_YES)
		{
			  save();
		}

	}
	else
		{
          	save();
		}
}
//---------------------------------------------------------------------------
 void __fastcall TForm1::Zapiszjako1Click(TObject *Sender)
{
	if(SavePictureDialog1->Execute())
	{
		srcFileName = SavePictureDialog1->FileName;
		zmodyfikowany = false;
		JPEGImage1->SaveToFile(srcFileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::acObrotWLewoExecute(TObject *Sender)
{
	//Obroc w lewo

	typedef  Byte TByteTriple[3];
	TByteTriple *PixelNew, *PixelOld;
	TBitmap  *Bitmap1, *Bitmap2;
	Bitmap1 = new Graphics::TBitmap;
	Bitmap2 = new Graphics::TBitmap;
	Bitmap1->Assign(JPEGImage1);
	Bitmap2->Width =Bitmap1->Height;
	Bitmap2->Height =Bitmap1->Width;
	Bitmap1->PixelFormat=pf24bit;
	Bitmap2->PixelFormat=pf24bit;

	ProgressBar1->Max = Bitmap2->Height;
	for(int j=0; j<Bitmap2->Height; j++)
	{
		PixelNew = (TByteTriple *) Bitmap2->ScanLine[j];
		ProgressBar1->Position = j;
		for(int i=0; i<Bitmap1->Height; i++)
		{

			PixelOld= (TByteTriple *)Bitmap1->ScanLine[i];

			PixelNew[i][0] = PixelOld[Bitmap1->Width-j-1][0];
			PixelNew[i][1] = PixelOld[Bitmap1->Width-j-1][1];
			PixelNew[i][2] = PixelOld[Bitmap1->Width-j-1][2];
		}
	}

	JPEGImage1->Assign(Bitmap2);
	pokazObraz();
	zmodyfikowany = true;
	ProgressBar1->Position = 0;
	delete(Bitmap1);
	delete(Bitmap2);


	/*
	int i,j;
	TBitmap  *Bitmap1, *Bitmap2;
	Bitmap1 = new Graphics::TBitmap;
	Bitmap2 = new Graphics::TBitmap;
	Bitmap1->Assign(JPEGImage1);
	Bitmap2->Width=Bitmap1->Height;
	Bitmap2->Height=Bitmap1->Width;
	for (int i=0; i<Bitmap1->Width;i++)
	{
	  for(int j=0; j<Bitmap1->Height; j++)
	  {
		   Bitmap2->Canvas->Pixels[Bitmap2->Width - j][i]= Bitmap1->Canvas->Pixels[i][j];
      }

	}

	JPEGImage1->Assign(Bitmap2);
	pokazObraz();
	delete Bitmap1;
	delete Bitmap2; */


	/*bitmap1 = new Graphics::TBitmap;

	bitmap1->Assign(JPEGImage1);
	TColor pomoc;

	ProgressBar1->Max = bitmap1->Height;

	if(bitmap1->Width == bitmap1->Height)
	{
		for(int i=0; i<bitmap1->Height/2; i++)
		{
			ProgressBar1->Position = i;

			for(int j=i;j<bitmap1->Width -1-i; j++)
			{
				pomoc = bitmap1->Canvas->Pixels[i][j];
				bitmap1->Canvas->Pixels[i][j] = bitmap1->Canvas->Pixels[bitmap1->Width -1 -j][i];
				bitmap1->Canvas->Pixels[bitmap1->Width -1 -j][i] = bitmap1->Canvas->Pixels[bitmap1->Height -i -1][bitmap1->Width -1 -j];  // dol -> prawo
				bitmap1->Canvas->Pixels[bitmap1->Height-i -1][bitmap1->Width -1-j] = bitmap1->Canvas->Pixels[j][bitmap1->Height -i -1];      // lewo -> dol
				bitmap1->Canvas->Pixels[j][bitmap1->Height -i -1] = pomoc;
			}
		}

		ProgressBar1->Position = 0;
		JPEGImage1->Assign(bitmap1);
		pokazObraz();
		zmodyfikowany = true;
		delete bitmap1;
	}
	else
	{
		Application->MessageBox(L"¯eby dokonaæ obrotu obraz musi byæ kwadratowy",L"Uwaga", MB_OK);
	}    */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::acObrotWPrawoExecute(TObject *Sender)
{

	//Obroc w prawo

	typedef  Byte TByteTriple[3];
	TByteTriple *PixelNew, *PixelOld;
	TBitmap  *Bitmap1, *Bitmap2;
	Bitmap1 = new Graphics::TBitmap;
	Bitmap2 = new Graphics::TBitmap;
	Bitmap1->Assign(JPEGImage1);
	Bitmap2->Width =Bitmap1->Height;
	Bitmap2->Height =Bitmap1->Width;
	Bitmap1->PixelFormat=pf24bit;
	Bitmap2->PixelFormat=pf24bit;

	ProgressBar1->Max = Bitmap2->Height;
	for(int j=0; j<Bitmap2->Height; j++)
	{
		PixelNew = (TByteTriple *) Bitmap2->ScanLine[j];
		ProgressBar1->Position = j;
		for(int i=0; i<Bitmap1->Height; i++)
		{

			PixelOld= (TByteTriple *)Bitmap1->ScanLine[i];

			PixelNew[Bitmap1->Width-i-1][0] = PixelOld[j][0];
			PixelNew[Bitmap1->Width-i-1][1] = PixelOld[j][1];
			PixelNew[Bitmap1->Width-i-1][2] = PixelOld[j][2];
		}
	}

		JPEGImage1->Assign(Bitmap2);
	pokazObraz();
	zmodyfikowany = true;
	ProgressBar1->Position = 0;
	delete(Bitmap1);
	delete(Bitmap2);


		/*
    bitmap1 = new Graphics::TBitmap;

	bitmap1->Assign(JPEGImage1);
	TColor pomoc;

	ProgressBar1->Max = bitmap1->Height;

	if(bitmap1->Width == bitmap1->Height)
	{
		for(int i=0; i<bitmap1->Height/2; i++)
		{
			ProgressBar1->Position = i;

			for(int j=i;j<bitmap1->Width -1-i; j++)
			{
				pomoc = bitmap1->Canvas->Pixels[i][j];
				bitmap1->Canvas->Pixels[i][j] = bitmap1->Canvas->Pixels[j][bitmap1->Height -i -1];
				bitmap1->Canvas->Pixels[j][bitmap1->Height -i -1] = bitmap1->Canvas->Pixels[bitmap1->Height -i -1][bitmap1->Width -1 -j];
				bitmap1->Canvas->Pixels[bitmap1->Height-i -1][bitmap1->Width -1-j] = bitmap1->Canvas->Pixels[bitmap1->Width -1 -j][i];
				bitmap1->Canvas->Pixels[bitmap1->Width -j -1][i] = pomoc;
			}
		}

		ProgressBar1->Position = 0;
		JPEGImage1->Assign(bitmap1);
		pokazObraz();
		zmodyfikowany = true;
		delete bitmap1;
	}
	else
	{
		Application->MessageBox(L"¯eby dokonaæ obrotu obraz musi byæ kwadratowy",L"Uwaga", MB_OK);
	}
	*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::acPelnyEkranExecute(TObject *Sender)
{
	TJPEGImage *JPEGImage1;

	JPEGImage1 = new TJPEGImage;
	JPEGImage1->LoadFromFile(FileListBox1->FileName);
	Form2->Image1->Picture->Assign(JPEGImage1);
	delete(JPEGImage1);
	Form2->ShowModal();
	delete(Form2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FileListBox1DblClick(TObject *Sender)
{

	srcFileName = FileListBox1->FileName;
	JPEGImage1->LoadFromFile(srcFileName);
	pokazObraz();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	mousePos.x = X;
	mousePos.y = Y;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{

	StatusBar1->Panels->Items[1]->Text = "x: " + IntToStr(X);
	StatusBar1->Panels->Items[2]->Text = "y: " + IntToStr(Y);

	if(Shift.Contains(ssLeft))
	{
		Image1->Canvas->DrawFocusRect(lastRect);
		lastRect.Left = mousePos.x;
		lastRect.Right = X;
		lastRect.Top = mousePos.y;
		lastRect.Bottom = Y;
		Image1->Canvas->DrawFocusRect(lastRect);
	}
 }

//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	sourceRect.Left = mousePos.x;
	sourceRect.Top = mousePos.y;
	sourceRect.Right = X;
	sourceRect.Bottom = Y;
	TBitmap *bitmap1;
	bitmap1 = new TBitmap;
	bitmap1->Assign(JPEGImage1);
	Image1->Canvas->CopyRect(Image1->ClientRect, bitmap1->Canvas, sourceRect);
	zmodyfikowany = true;
    delete bitmap1;
}


//---------------------------------------------------------------------------


void __fastcall TForm1::acWyjdzExecute(TObject *Sender)
{
	delete(this->JPEGImage1);
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	int mb_return;
	CanClose = true;

	if(zmodyfikowany)
	{
		mb_return = Application->MessageBox(L"Czy chcesz zapisaæ zmiany do pliku?", L"Zapisz zmiany", MB_YESNOCANCEL | MB_ICONQUESTION);
		if(mb_return == ID_YES) acZapisz->Execute();

		if(mb_return == ID_CANCEL) CanClose = false;
	}
}
//---------------------------------------------------------------------------


