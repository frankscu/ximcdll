#include "TXIMCGUI.h"

ClassImp(TXIMCGUI);

TXIMCGUI::TXIMCGUI(const TGWindow *p, UInt_t w, UInt_t h)
   : TGMainFrame(p, w, h)
{

   fHor1 = new TGHorizontalFrame(this, 60, 20, kFixedWidth);
   fExit = new TGTextButton(fHor1, "&Exit", "gApplication->Terminate(0)");
   fHor1->AddFrame(fExit, new TGLayoutHints(kLHintsTop | kLHintsLeft |
                                            kLHintsExpandX, 4, 4, 4, 4));
   AddFrame(fHor1,new TGLayoutHints(kLHintsBottom | kLHintsRight, 2, 2, 5, 1));

   fNumber = new TGNumberEntry(this, 0, 9,999, TGNumberFormat::kNESInteger,
                                               TGNumberFormat::kNEANonNegative,
                                               TGNumberFormat::kNELLimitMinMax,
                                               0, 99999);
   fNumber->Connect("ValueSet(Long_t)", "TXIMCGUI", this, "DoSetlabel()");
   (fNumber->GetNumberEntry())->Connect("ReturnPressed()", "TXIMCGUI", this,
                                        "DoSetlabel()");
   AddFrame(fNumber, new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 5, 5));
   fGframe = new TGGroupFrame(this, "Value");
   fLabel = new TGLabel(fGframe, "No input.");
   fGframe->AddFrame(fLabel, new TGLayoutHints(kLHintsTop | kLHintsLeft,
                                               5, 5, 5, 5));
   AddFrame(fGframe, new TGLayoutHints(kLHintsExpandX, 2, 2, 1, 1));

   SetCleanup(kDeepCleanup);
   SetWindowName("Number Entry");
   MapSubwindows();
   Resize(GetDefaultSize());
   MapWindow();
}

TXIMCGUI::~TXIMCGUI()
{
   // Destructor.

   Cleanup();
}

void TXIMCGUI::DoSetlabel()
{
   // Slot method connected to the ValueSet(Long_t) signal.
   // It displays the value set in TGNumberEntry widget.

   fLabel->SetText(Form("%ld",fNumber->GetNumberEntry()->GetIntNumber()));

   // Parent frame Layout() method will redraw the label showing the new value.
   fGframe->Layout();
}
