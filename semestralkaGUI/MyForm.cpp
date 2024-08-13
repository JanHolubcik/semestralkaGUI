#include "MyForm.h"
#include "structures/heap_monitor.h"
using namespace System;
using namespace System::Windows::Forms;

void main(cli::array<System::String ^> ^ args)
{
    initHeapMonitor();

    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();

    loader *loadTable = new loader();
    semestralkaGUI::MyForm form(loadTable);
    Application::Run(% form);
    delete loadTable;

   
}