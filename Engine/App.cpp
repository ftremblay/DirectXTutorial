#include <stdio.h>
#include "pch.h"

using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

ref class App sealed : public IFrameworkView
{
public :
	virtual void Initialize(CoreApplicationView^ appView)
	{
		appView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);
	}
	virtual void SetWindow(CoreWindow^ window){
		window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &App::OnPointerPressed);
		window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::OnKeyDown);
		window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &App::OnKeyUp);
	}
	virtual void Load(String^ EntryPoint) {}
	virtual void Run () {
		CoreWindow^ window = CoreWindow::GetForCurrentThread();
		window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
	}
	virtual void Uninitialize() {}

	void OnActivated(CoreApplicationView^ coreAppView, IActivatedEventArgs^ args) {
		CoreWindow^ window = CoreWindow::GetForCurrentThread();
		window->Activate();
	}
	void OnPointerPressed(CoreWindow^ window, PointerEventArgs^ args) {
		MessageDialog dialog("Thank you for noticing this notice.", "Notice!");
		dialog.ShowAsync();
	}
	void OnKeyDown(CoreWindow^ window, KeyEventArgs^ args) {
		ShowKeyDownDialogBox(args->VirtualKey);
	}
	void OnKeyUp(CoreWindow^ window, KeyEventArgs^ args) {
		ShowKeyUpDialogBox(args->VirtualKey);
	}
	void OnPointerWheelChanged(CoreWindow^ sender, PointerEventArgs^ args) {
		int wheel = args->CurrentPoint->Properties->MouseWheelDelta;
	}
private:
	void ShowKeyDownDialogBox(const VirtualKey& key) {
		MessageDialog dialog("Key down: " + key.ToString());
		dialog.ShowAsync();
	}

	void ShowKeyUpDialogBox(const VirtualKey& key) {
		MessageDialog dialog("Key up: " + key.ToString());
		dialog.ShowAsync();
	}
};

ref class AppSource sealed : IFrameworkViewSource
{
public:
	virtual IFrameworkView^ CreateView() {
		return ref new App();
	}
};

[MTAThread]
int main(Array<String^>^ args) {
	CoreApplication::Run(ref new AppSource());
	return 0;
}