#include <TApplication.h>
#include <TGClient.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TGLayout.h>
#include <TGWindow.h>
#include <TGLabel.h>
#include <TGNumberEntry.h>
#include <TString.h>

class TXIMCGUI : public TGMainFrame {

private:
   TGCompositeFrame    *fHor1;
   TGTextButton        *fExit;
   TGGroupFrame        *fGframe;
   TGNumberEntry       *fNumber;
   TGLabel             *fLabel;

public:
   TXIMCGUI(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~TXIMCGUI();
   void DoSetlabel();

   ClassDef(TXIMCGUI, 2)
};
