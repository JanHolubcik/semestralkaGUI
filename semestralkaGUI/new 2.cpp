#pragma once
#include <iostream>
#include "loader.h"
#include "sorter.h"
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include "criterio.h"
#include "cType.h"
#include "filter.h"
#include "fUJByValue.h"
#include "filterByInterval.h"
#include "universalFilter.h"
#include "compositeFilter.h"
#include "criterioName.h"
#include "cBelongsTo.h"
#include "kUJVzdelavanieGroupSum.h"
#include "cUJVzdelavanieGroupRatio.h"
#include "cUJVekSum.h"
#include "cUJVekRatio.h"
#include "cUJVekovaSkupina.h"
#include "cUJVekovaSkupinaRatio.h"

namespace semestralkaGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(loader* loadTables)
		{
			InitializeComponent();
			loaderUJ = loadTables;
			loaderUJ->loadTables();
			comboBoxUJ->SelectedIndex = 0;
			comboBox2->SelectedIndex = 0;

		    obce = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
			okresy = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
			kraje = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
			krajiny = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
			filteredValues = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();;
			sortTable = new sorter();
			compFilter = new compositeFilter<uzemnaJednotka*>();
			findByBisection = new bisectionName();
			for (auto item : loaderUJ->getObce()) {
				obce->insert(item->accessData()->getSortNumber(), item->accessData());
			
			}
			for (auto item : loaderUJ->getOkresy()) {
				okresy->insert(item->accessData()->getSortNumber(), item->accessData());
			}
			for (auto item : loaderUJ->getKraje()) {
				kraje->insert(item->accessData()->getSortNumber(), item->accessData());
			}		
			for (auto item : loaderUJ->getKrajiny()) {
				krajiny->insert(item->accessData()->getSortNumber(), item->accessData());
			}
			
			structures::UnsortedSequenceTable<int, uzemnaJednotka*> *sortingTable = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
			
			sortingTable->assign(*obce);
			sortTable->sortByName(*sortingTable, 0);
			int i = 0;
			obce->clear();
			for (auto item : *sortingTable) {
				obce->insert(i, item->accessData());
				i++;
			}
			sortingTable->assign(*okresy);
			sortTable->sortByName(*sortingTable, 0);
			okresy->clear();
			 i = 0;
			for (auto item : *sortingTable) {
				okresy->insert(i, item->accessData());
				i++;
			}
			sortingTable->assign(*kraje);
			sortTable->sortByName(*sortingTable, 0);
			kraje->clear();
			 i = 0;
			for (auto item : *sortingTable) {
				kraje->insert(i, item->accessData());
				i++;
			}
			sortingTable->assign(*krajiny);
			sortTable->sortByName(*sortingTable, 0);
			krajiny->clear();
			 i = 0;
			for (auto item : *sortingTable) {
				krajiny->insert(i, item->accessData());
				i++;
			}
			delete sortingTable;
		
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			if (!wasDeleted) {
				delete obce;
				delete okresy;
				delete kraje;
				delete krajiny;
				delete sortTable;
				delete findByBisection;
				delete filteredValues;
				delete compFilter;
				wasDeleted = true;
			}
		}

	private: bool wasDeleted = false;
	private: int numberOfColumns = 0;
	private: loader* loaderUJ;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBoxUJ;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ dataGridViewUJ;
	private:






	private: System::Windows::Forms::TextBox^ textBoxFind;
	private: System::Windows::Forms::Label^ label2;

	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>* obce = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>* okresy = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>*kraje = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>*krajiny = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>* filteredValues = nullptr;
	private: sorter* sortTable =nullptr;
	private: bisectionName* findByBisection = nullptr;
	private: compositeFilter<uzemnaJednotka*>* compFilter = nullptr;


private: System::Windows::Forms::Button^ button2;
private: System::Windows::Forms::ComboBox^ comboBox1;
private: System::Windows::Forms::TextBox^ textBox1;
private: System::Windows::Forms::TextBox^ textBox2;
private: System::Windows::Forms::CheckBox^ checkBox1;
private: System::Windows::Forms::Button^ button3;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Button^ button4;

private: System::Windows::Forms::ComboBox^ comboBox2;
private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
private: System::Windows::Forms::CheckBox^ checkBox2;
private: System::Windows::Forms::DataGridView^ dataGridView1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
private: System::Windows::Forms::Button^ button5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Code;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column16;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column10;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column11;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column12;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column13;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column14;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column15;


























	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxUJ = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridViewUJ = (gcnew System::Windows::Forms::DataGridView());
			this->textBoxFind = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->Code = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column16 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column14 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column15 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewUJ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 7);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(114, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Zvoľ územnú jednotku";
			// 
			// comboBoxUJ
			// 
			this->comboBoxUJ->FormattingEnabled = true;
			this->comboBoxUJ->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Obec", L"Okres", L"Kraj", L"Slovensko" });
			this->comboBoxUJ->Location = System::Drawing::Point(11, 26);
			this->comboBoxUJ->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->comboBoxUJ->Name = L"comboBoxUJ";
			this->comboBoxUJ->Size = System::Drawing::Size(112, 21);
			this->comboBoxUJ->TabIndex = 2;
			this->comboBoxUJ->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxUJ_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(9, 50);
			this->button1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(284, 35);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Vypíš uzemné jednotky";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::loadToDataGrid);
			// 
			// dataGridViewUJ
			// 
			this->dataGridViewUJ->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridViewUJ->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewUJ->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(13) {
				this->Code,
					this->Column16, this->Column5, this->Column6, this->Column7, this->Column8, this->Column9, this->Column10, this->Column11, this->Column12,
					this->Column13, this->Column14, this->Column15
			});
			this->dataGridViewUJ->Location = System::Drawing::Point(26, 217);
			this->dataGridViewUJ->Margin = System::Windows::Forms::Padding(0);
			this->dataGridViewUJ->Name = L"dataGridViewUJ";
			this->dataGridViewUJ->RowHeadersVisible = false;
			this->dataGridViewUJ->RowHeadersWidth = 51;
			this->dataGridViewUJ->RowTemplate->Height = 24;
			this->dataGridViewUJ->Size = System::Drawing::Size(1268, 526);
			this->dataGridViewUJ->TabIndex = 3;
			this->dataGridViewUJ->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellContentClick);
			// 
			// textBoxFind
			// 
			this->textBoxFind->Location = System::Drawing::Point(130, 28);
			this->textBoxFind->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBoxFind->Name = L"textBoxFind";
			this->textBoxFind->Size = System::Drawing::Size(163, 20);
			this->textBoxFind->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(127, 7);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Vyhľadávanie";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(9, 89);
			this->button2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(72, 20);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Ukáž filtre";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::showFilter);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"Podľa názvu", L"Poďla typu", L"Podľa príslušnosti",
					L"Podľa počtu vzdelania ", L"Podľa podielu vzdelanie", L"Podľa počtu veku", L"Podľa podielu veku", L"Podľa počtu vekovej skupiny",
					L"Podľa podielu vekovej skupiny"
			});
			this->comboBox1->Location = System::Drawing::Point(86, 87);
			this->comboBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(208, 21);
			this->comboBox1->TabIndex = 7;
			this->comboBox1->Visible = false;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::showValueFields);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(9, 132);
			this->textBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(140, 20);
			this->textBox1->TabIndex = 8;
			this->textBox1->Visible = false;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(153, 132);
			this->textBox2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(140, 20);
			this->textBox2->TabIndex = 9;
			this->textBox2->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(9, 112);
			this->checkBox1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(145, 17);
			this->checkBox1->TabIndex = 10;
			this->checkBox1->Text = L"Filtrovať podla intervalu \?";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->Visible = false;
			this->checkBox1->Click += gcnew System::EventHandler(this, &MyForm::checkBox1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(9, 184);
			this->button3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(284, 32);
			this->button3->TabIndex = 11;
			this->button3->Text = L"Pridaj filter";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(208, 72);
			this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 12;
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(304, 184);
			this->button4->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(188, 32);
			this->button4->TabIndex = 13;
			this->button4->Text = L"Filtruj";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::filterUJ);
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Obec", L"Okres", L"Kraj", L"Slovensko" });
			this->comboBox2->Location = System::Drawing::Point(9, 161);
			this->comboBox2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(285, 21);
			this->comboBox2->TabIndex = 15;
			this->comboBox2->Visible = false;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox2_SelectedIndexChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(195, 112);
			this->checkBox2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(105, 17);
			this->checkBox2->TabIndex = 16;
			this->checkBox2->Text = L"Ženské pohlavie";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->Visible = false;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->Column1,
					this->Column2, this->Column3, this->Column4
			});
			this->dataGridView1->Location = System::Drawing::Point(304, 26);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(0);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(379, 156);
			this->dataGridView1->TabIndex = 17;
			this->dataGridView1->Visible = false;
			// 
			// Column1
			// 
			this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->Column1->HeaderText = L"Filter";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 54;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Podľa";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->Width = 125;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L" ";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->Width = 125;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L" ";
			this->Column4->MinimumWidth = 6;
			this->Column4->Name = L"Column4";
			this->Column4->Width = 125;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(497, 184);
			this->button5->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(186, 31);
			this->button5->TabIndex = 18;
			this->button5->Text = L"Resetuj filtre";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// Code
			// 
			this->Code->HeaderText = L"Code";
			this->Code->MinimumWidth = 6;
			this->Code->Name = L"Code";
			// 
			// Column16
			// 
			this->Column16->HeaderText = L"Official title";
			this->Column16->Name = L"Column16";
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"bez ukončeného vzdelania ";
			this->Column5->MinimumWidth = 6;
			this->Column5->Name = L"Column5";
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"základné vzdelanie ";
			this->Column6->MinimumWidth = 6;
			this->Column6->Name = L"Column6";
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"stredné odborné vzdelanie ";
			this->Column7->MinimumWidth = 6;
			this->Column7->Name = L"Column7";
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"úplné stredné vzdelanie";
			this->Column8->MinimumWidth = 6;
			this->Column8->Name = L"Column8";
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"vyššie odborné vzdelanie";
			this->Column9->MinimumWidth = 6;
			this->Column9->Name = L"Column9";
			// 
			// Column10
			// 
			this->Column10->HeaderText = L"vysokoškolské vzdelanie";
			this->Column10->MinimumWidth = 6;
			this->Column10->Name = L"Column10";
			// 
			// Column11
			// 
			this->Column11->HeaderText = L"bez školského vzdelania";
			this->Column11->MinimumWidth = 6;
			this->Column11->Name = L"Column11";
			// 
			// Column12
			// 
			this->Column12->HeaderText = L"nezistené ";
			this->Column12->MinimumWidth = 6;
			this->Column12->Name = L"Column12";
			// 
			// Column13
			// 
			this->Column13->HeaderText = L"Predproduktívny";
			this->Column13->MinimumWidth = 6;
			this->Column13->Name = L"Column13";
			// 
			// Column14
			// 
			this->Column14->HeaderText = L"Produktívny";
			this->Column14->MinimumWidth = 6;
			this->Column14->Name = L"Column14";
			// 
			// Column15
			// 
			this->Column15->HeaderText = L"Postproduktívny";
			this->Column15->MinimumWidth = 6;
			this->Column15->Name = L"Column15";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1311, 762);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBoxFind);
			this->Controls->Add(this->dataGridViewUJ);
			this->Controls->Add(this->comboBoxUJ);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewUJ))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void test(System::Object^ sender, System::EventArgs^ e) {
		this->label1->Text = "ahoj";
	
	}
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		
		
	}
private: System::Void comboBoxUJ_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

}
	private: System::Void loadToDataGrid(System::Object^ sender, System::EventArgs^ e) {
		
		structures::UnsortedSequenceTable<int, uzemnaJednotka*>* UJ = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
		switch (comboBoxUJ->SelectedIndex) {
		case 0: {
			UJ->assign(*obce);
			break;
		}
		case 1: {
			UJ->assign(*okresy);
			break;
		}
		case 2: {
			UJ->assign(*kraje);
			break;
		}
		default: {
			UJ->assign(*krajiny);
			break;
		}
		}

		int i = 0;
		dataGridViewUJ->Rows->Clear();
	
		String^ code = gcnew String(textBoxFind->Text);
		
		if (!code->IsNullOrEmpty(code)) {
			bool found = findByBisection->findAllUJByBisection(msclr::interop::marshal_as<wstring>(code), *UJ);
			
			if (!found) {
				structures::UnsortedSequenceTable<int, uzemnaJednotka*>* containsString = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
				for (auto item : *UJ) {
					size_t lol = msclr::interop::marshal_as<wstring>(code).find(item->accessData()->getOfficialTitle());
					if (SIZE_MAX != item->accessData()->getOfficialTitle().find(msclr::interop::marshal_as<wstring>(code))) {
						containsString->insert(item->getKey(), item->accessData());
					}
				}
				UJ->assign(*containsString);
				delete containsString;
			}
			else {
				UJ->assign(findByBisection->getAllFoundByBisection());
			}
		}
		
	for (auto item : *UJ) {
		dataGridViewUJ->Rows->Add();
		String^ code = gcnew String(item->accessData()->getCode().c_str());
		String^ officialTitle = gcnew String(item->accessData()->getOfficialTitle().c_str());
		dataGridViewUJ->Rows[i]->Cells[0]->Value = code;
		dataGridViewUJ->Rows[i]->Cells[1]->Value = officialTitle;
		size_t j = 2;
		for (j ; j < item->accessData()->getVzdelavanie().size()+2; j++)
		{
			int^ number = gcnew int(item->accessData()->getVzdelavanie().at(j-2));
			dataGridViewUJ->Rows[i]->Cells[j]->Value = number;
		}
		for (size_t k=0; k < (item->accessData()->getVekovaSkupina().size()/2); k++)
		{
			int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k+3));
			dataGridViewUJ->Rows[i]->Cells[j+k]->Value = number;
		}
		
		i++;
	}
	


	delete UJ;
	
}
private: System::Void showFilter(System::Object^ sender, System::EventArgs^ e) {
	comboBox1->Visible = !comboBox1->Visible;
	checkBox1->Visible = !checkBox1->Visible;

	button4->Visible = !button4->Visible;
	button3->Visible = !button3->Visible;
	textBox1->Visible = !textBox1->Visible;
	textBox2->Visible = !textBox2->Visible;
	dataGridView1->Visible = !dataGridView1->Visible;
	if (textBox1->Visible || textBox2->Visible) {
		textBox1->Visible = false;
		textBox2->Visible = false;
	}
}
private: System::Void showValueFields(System::Object^ sender, System::EventArgs^ e) {
	textBox1->Visible = false;
	textBox2->Visible = false;
	comboBox2->Visible = false;
	
	checkBox1->Visible = false;
		switch (comboBox1->SelectedIndex) {
		case 0: {
			textBox1->Visible = true;
			break;
		}
		case 1: {
			comboBox2->Visible = true;
			comboBox2->Items->Clear();
			comboBox2->Visible = true;
			comboBox2->Items->Add(L"obec");
			comboBox2->Items->Add(L"okres");
			comboBox2->Items->Add(L"kraj");
			comboBox2->Items->Add(L"krajina");
			comboBox2->SelectedIndex = 0;
			break;
		}
		case 2: {
			textBox1->Visible = true;
	
			break;
		}
		case 3: {	
			textBox1->Visible = true;
			checkBox1->Visible = true;
			comboBox2->Visible = true;
			comboBox2->Items->Clear();
			comboBox2->Items->Add(L"bez ukončeného vzdelania");
			comboBox2->Items->Add(L"základné vzdelanie");
			comboBox2->Items->Add(L"stredné odborné vzdelanie");
			comboBox2->Items->Add(L"úplné stredné vzdelanie");
			comboBox2->Items->Add(L"vyššie odborné vzdelanie");
			comboBox2->Items->Add(L"vysokoškolské vzdelanie");
			comboBox2->Items->Add(L"bez školského vzdelania");
			comboBox2->Items->Add(L"nezistené ");
			comboBox2->SelectedIndex = 0;
			if (checkBox1->Checked == true) {
				textBox2->Visible = true;
			}
			break;
		}
		case 4: {
			textBox1->Visible = true;
			checkBox1->Visible = true;
			comboBox2->Visible = true;
			comboBox2->Items->Clear();
			comboBox2->Items->Add(L"bez ukončeného vzdelania");
			comboBox2->Items->Add(L"základné vzdelanie");
			comboBox2->Items->Add(L"stredné odborné vzdelanie");
			comboBox2->Items->Add(L"úplné stredné vzdelanie");
			comboBox2->Items->Add(L"vyššie odborné vzdelanie");
			comboBox2->Items->Add(L"vysokoškolské vzdelanie");
			comboBox2->Items->Add(L"bez školského vzdelania");
			comboBox2->Items->Add(L"nezistené ");
			comboBox2->SelectedIndex = 0;
			if (checkBox1->Checked == true) {
				textBox2->Visible = true;
			}
			break;
		}
		case 5: {
			checkBox1->Visible = true;
			textBox1->Visible = true;
			if (checkBox1->Checked == true) {
				textBox2->Visible = true;
			}
			break;
		}
		case 6: {
			checkBox1->Visible = true;
			textBox1->Visible = true;
			if (checkBox1->Checked == true) {
				textBox2->Visible = true;
			}
			break;
		}
		case 7: {
			textBox1->Visible = true;
			checkBox1->Visible = true;
			comboBox2->Visible = true;
			comboBox2->Items->Clear();
			comboBox2->Items->Add(L"Predproduktívni");
			comboBox2->Items->Add(L"Produktívni");
			comboBox2->Items->Add(L"Poproduktívni");
			comboBox2->SelectedIndex = 0;
			//textBox1->Visible = true;
			if (checkBox1->Checked == true) {
				textBox2->Visible = true;
			}
			break;
		}
		case 8: {
			textBox1->Visible = true;
			checkBox1->Visible = true;
			comboBox2->Visible = true;
			comboBox2->Items->Clear();
			comboBox2->Items->Add(L"Predproduktívni");
			comboBox2->Items->Add(L"Produktívni");
			comboBox2->Items->Add(L"Poproduktívni");
			comboBox2->SelectedIndex = 0;
			//textBox1->Visible = true;
			if (checkBox1->Checked == true) {
				textBox2->Visible = true;
			}
			break;
		}
		default: {

			break;
		}
		}
}
private: System::Void checkBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (checkBox1->Checked == true) {
		textBox2->Visible = true;
	}
	else {
		textBox2->Visible = false;
	}
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ code = gcnew String(textBox1->Text);
	String^ textValue2 = gcnew String(textBox2->Text);
	int value1 = 0;
	Int32::TryParse(code, value1);
	int value2 = 0;
	double doubleValue1 = 0;
	double doubleValue2 = 0;
	bool isNumber1 = Int32::TryParse(code, value1);
	bool isNumber2 = Int32::TryParse(textValue2, value2);
	bool isdouble1 = Double::TryParse(code, doubleValue1);
	bool isdouble2 = Double::TryParse(textValue2, doubleValue2);
	//if (!code->IsNullOrEmpty(code)) {
		switch (comboBox1->SelectedIndex) {
		case 0: {

			bool found = findByBisection->findUJByBisection(msclr::interop::marshal_as<wstring>(code), *krajiny);
			if (!found) {
				found = findByBisection->findUJByBisection(msclr::interop::marshal_as<wstring>(code), *kraje);
			}
			if (!found) {
				found = findByBisection->findUJByBisection(msclr::interop::marshal_as<wstring>(code), *okresy);
			}
			if (!found) {
				found = findByBisection->findUJByBisection(msclr::interop::marshal_as<wstring>(code), *obce);
			}
			
			if (found) {
				criterioName* cName = new criterioName();
				fUJByValue<std::wstring, uzemnaJednotka*, std::wstring>* filterbyvalue =
					new  fUJByValue<std::wstring, uzemnaJednotka*, std::wstring>(cName, cName->evaluate(&findByBisection->getFoundByBisection()));
				fUJByValue<std::wstring, uzemnaJednotka*, std::wstring>* filterby = filterbyvalue;
				compFilter->addFilter(filterbyvalue);
				label3->Text = "Filter bol úspešne pridaný";
				addNewColumn(L"Podľa hodnoty", cName->evaluate(&findByBisection->getFoundByBisection()), L"", L"");
			//	delete cName;
			//	delete filterbyvalue;
			}
			else {
				label3->Text = "Nenašla sa územná jednotka s názvom: " + code;
			}
			break;
		}
		case 1: {
		
			cType* type = new cType();
			fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue =
				new  fUJByValue<std::wstring, uzemnaJednotka*, int>(type, comboBox2->SelectedIndex);
			addNewColumn(L"Podľa typu", (msclr::interop::marshal_as<wstring>(comboBox2->Text)), L"", L"");
			compFilter->addFilter(filterbyvalue);
			break;
		}
		case 2: {		
				bool found = findByBisection->findUJByBisection(msclr::interop::marshal_as<wstring>(code), *krajiny);
				if (!found) {
					found = findByBisection->findUJByBisection(msclr::interop::marshal_as<wstring>(code), *kraje);
				}
				if (!found) {
					found = findByBisection->findUJByBisection(msclr::interop::marshal_as<wstring>(code), *okresy);
				}
				if (found) {

					cBelongsTo* cBelongTo = new cBelongsTo(&findByBisection->getFoundByBisection());
					fUJByValue<std::wstring, uzemnaJednotka*, bool>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, bool>(cBelongTo, true);
					addNewColumn(L"Podľa príslušnosti", msclr::interop::marshal_as<wstring>(code), L"", L"");
					compFilter->addFilter(filterbyvalue);
					label3->Text = "Filter bol úspešne pridaný";
				}
				else {
					label3->Text = "Nenašla sa územná jednotka s názvom: " + code;
				}
			
			break;
		}
		case 3: {
			if (!code->IsNullOrEmpty(code)) {
				if (checkBox1->Checked) {
					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isNumber1 && isNumber2) {
							int i = comboBox2->SelectedIndex;
							kUJVzdelavanieSum* vzdelavanie = new kUJVzdelavanieSum(comboBox2->SelectedIndex);

							filterByInterval<std::wstring, uzemnaJednotka*, int>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, int>(vzdelavanie, value1, value2);
							addNewColumn(L"Vzdelavania", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label3->Text = "Filter bol úspešne pridaný";
						}
						else {
							label3->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label3->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if(isNumber1){
					kUJVzdelavanieSum* vzdelavanie = new kUJVzdelavanieSum(comboBox2->SelectedIndex);
					fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, int>(vzdelavanie, value1);
					addNewColumn(L"Vzdelavania", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code), L"");
					compFilter->addFilter(filterbyvalue);
					label3->Text = "Filter bol úspešne pridaný";
					}
					else {
						label3->Text = "Hodnota v poli nie je číslo.";
					}
				}		
			}
			else {
				label3->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		case 4: {
			if (!code->IsNullOrEmpty(code)) {
				if (checkBox1->Checked) {
					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isdouble1 && isdouble2) {
							cUJVzdelavanieGroupRatio* vzdelavanie = new cUJVzdelavanieGroupRatio(comboBox2->SelectedIndex);
							filterByInterval<std::wstring, uzemnaJednotka*, double>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, double>(vzdelavanie, doubleValue1, doubleValue2);
							addNewColumn(L"Vzdelavania podiel", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label3->Text = "Filter bol úspešne pridaný";
						}
						else {
							label3->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label3->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isdouble1) {
						cUJVzdelavanieGroupRatio* vzdelavanie = new cUJVzdelavanieGroupRatio(comboBox2->SelectedIndex);
						fUJByValue<std::wstring, uzemnaJednotka*, double>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, double>(vzdelavanie, doubleValue1);
						addNewColumn(L"Vzdelavania podiel", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code), L"");
						compFilter->addFilter(filterbyvalue);
						label3->Text = "Filter bol úspešne pridaný";
					} 
					else {
						label3->Text = "Hodnota v poli nie je číslo.";
					}
				}
			}
			else {
				label3->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		case 5: {
			if (!code->IsNullOrEmpty(code)) {
				int pohlavie=0;
				if (checkBox2->Checked)
				{
					pohlavie = 1;
				}
				if (checkBox1->Checked) {
					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isNumber1 && isNumber2) {
							cUJVekGroupSum* criterioFilter = new cUJVekGroupSum(comboBox2->SelectedIndex, pohlavie);
							
							filterByInterval<std::wstring, uzemnaJednotka*, int>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, int>
								(criterioFilter, value1, value2);
							addNewColumn(L"Vek", checkBox2->Checked ? L"Muž" : L"Žena", msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label3->Text = "Filter bol úspešne pridaný";
						}
						else {
							label3->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label3->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isNumber1) {
						cUJVekGroupSum* criterioFilter = new cUJVekGroupSum(comboBox2->SelectedIndex, pohlavie);
						fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, int>(criterioFilter, value1);
						addNewColumn(L"Vek", checkBox2->Checked ? L"Muž" : L"Žena", msclr::interop::marshal_as<wstring>(code), L"");
						compFilter->addFilter(filterbyvalue);
						label3->Text = "Filter bol úspešne pridaný";
					}
					else {
						label3->Text = "Hodnota v poli nie je číslo.";
					}
				}
			}
			else {
				label3->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		case 6: {
			if (!code->IsNullOrEmpty(code)) {
				int pohlavie = 0;
				if (checkBox2->Checked)
				{
					pohlavie = 1;
				}
				if (checkBox1->Checked) {
					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isdouble1 && isdouble2) {
						cUJVekRatio* criterioFilter = new cUJVekRatio(comboBox2->SelectedIndex, pohlavie);
						
						filterByInterval<std::wstring, uzemnaJednotka*, double>* filter =
							new  filterByInterval<std::wstring, uzemnaJednotka*, double>(criterioFilter, doubleValue1, doubleValue2);
						addNewColumn(L"Vek podiel", checkBox2->Checked ? L"Muž" : L"Žena", msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
						compFilter->addFilter(filter);
						label3->Text = "Filter bol úspešne pridaný";
						}
						else {
							label3->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label3->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isdouble1){
					cUJVekRatio* criterioFilter = new cUJVekRatio(comboBox2->SelectedIndex, pohlavie);
					fUJByValue<std::wstring, uzemnaJednotka*, double>* filterbyvalue = 
						new  fUJByValue<std::wstring, uzemnaJednotka*, double>(criterioFilter, doubleValue1);
					addNewColumn(L"Vek podiel", checkBox2->Checked ? L"Muž" : L"Žena", msclr::interop::marshal_as<wstring>(code), L"");
					compFilter->addFilter(filterbyvalue);
					
					label3->Text = "Filter bol úspešne pridaný";
					}
					else {
						label3->Text = "Hodnota v poli nie je číslo.";
					}
				}
			}
			else {
				label3->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		case 7: {
			if (!code->IsNullOrEmpty(code)) {
				if (checkBox1->Checked) {
					if (isNumber1 && isNumber2) {
						if (!textValue2->IsNullOrEmpty(textValue2))
						{
							cUJVekovaSkupina* criterioFilter = new cUJVekovaSkupina(comboBox2->SelectedIndex);
							filterByInterval<std::wstring, uzemnaJednotka*, int>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, int>
								(criterioFilter, value1, value2);
							addNewColumn(L"Vek skupina", msclr::interop::marshal_as<wstring>(checkBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label3->Text = "Filter bol úspešne pridaný";
						}
						else {
							label3->Text = "Pre interval treba vyplniť aj druhé pole!";
						}
					}
					else {
						label3->Text = "Obidve alebo len jedna hodnota nie je číslo.";
					}
				}
				else {
					if (isNumber1) {
						cUJVekovaSkupina* criterioFilter = new cUJVekovaSkupina(comboBox2->SelectedIndex);
						fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue =
							new  fUJByValue<std::wstring, uzemnaJednotka*, int>(criterioFilter, value1);
						addNewColumn(L"Vek skupina", msclr::interop::marshal_as<wstring>(checkBox2->Text), msclr::interop::marshal_as<wstring>(code), L"");
						compFilter->addFilter(filterbyvalue);
						label3->Text = "Filter bol úspešne pridaný";
					}
					else {
						label3->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
			}
			else {
				label3->Text = "Hodnota v poli nie je číslo.";
			}
			break;
		}
		default: {
			if (!code->IsNullOrEmpty(code)) {

				if (checkBox1->Checked) {

					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isdouble1 && isdouble2) {
							cUJVekovaSkupinaRatio* vzdelavanie = new cUJVekovaSkupinaRatio(comboBox2->SelectedIndex);
							filterByInterval<std::wstring, uzemnaJednotka*, double>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, double>(vzdelavanie, doubleValue1, doubleValue2);
							addNewColumn(L"Vek skupina podiel", msclr::interop::marshal_as<wstring>(checkBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label3->Text = "Filter bol úspešne pridaný";
						}
						else {
							label3->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label3->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isdouble1){
					cUJVekovaSkupinaRatio* vzdelavanie = new cUJVekovaSkupinaRatio(comboBox2->SelectedIndex);
					fUJByValue<std::wstring, uzemnaJednotka*, double>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, double>(vzdelavanie, doubleValue1);
					addNewColumn(L"Vek skupina podiel", msclr::interop::marshal_as<wstring>(comboBox2->Text), L"", L"");
					compFilter->addFilter(filterbyvalue);
					label3->Text = "Filter bol úspešne pridaný";
					}
					else {
						label3->Text = "Hodnota v poli nie je číslo.";
					}
				}
			}
			else {
				label3->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		}
	//}

}
private: System::Void filterUJ(System::Object^ sender, System::EventArgs^ e) {
	label3->Text = "Filtruje sa!";
	int i = 0;
	dataGridViewUJ->Rows->Clear();

	for (auto item : *obce) {
		if(compFilter->matchesFilterAnd(item->accessData())){
	
		dataGridViewUJ->Rows->Add();
		String^ code = gcnew String(item->accessData()->getCode().c_str());
		String^ officialTitle = gcnew String(item->accessData()->getOfficialTitle().c_str());
		dataGridViewUJ->Rows[i]->Cells[0]->Value = code;
		dataGridViewUJ->Rows[i]->Cells[1]->Value = officialTitle;
		size_t j = 2;
		for (j; j < item->accessData()->getVzdelavanie().size() + 2; j++)
		{
			int^ number = gcnew int(item->accessData()->getVzdelavanie().at(j - 2));
			dataGridViewUJ->Rows[i]->Cells[j]->Value = number;
		}
		for (size_t k = 0; k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
		{
			int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
			dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
		}

		i++;
		}
	}
	for (auto item : *okresy) {
		if (compFilter->matchesFilterAnd(item->accessData())) {

			dataGridViewUJ->Rows->Add();
			String^ code = gcnew String(item->accessData()->getCode().c_str());
			String^ officialTitle = gcnew String(item->accessData()->getOfficialTitle().c_str());
			dataGridViewUJ->Rows[i]->Cells[0]->Value = code;
			dataGridViewUJ->Rows[i]->Cells[1]->Value = officialTitle;
			size_t j = 2;
			for (j; j < item->accessData()->getVzdelavanie().size() + 2; j++)
			{
				int^ number = gcnew int(item->accessData()->getVzdelavanie().at(j - 2));
				dataGridViewUJ->Rows[i]->Cells[j]->Value = number;
			}
			for (size_t k = 0; k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
			{
				int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
				dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
			}

			i++;
		}
	}
		for (auto item : *kraje) {
			if (compFilter->matchesFilterAnd(item->accessData())) {

				dataGridViewUJ->Rows->Add();
				String^ code = gcnew String(item->accessData()->getCode().c_str());
				String^ officialTitle = gcnew String(item->accessData()->getOfficialTitle().c_str());
				dataGridViewUJ->Rows[i]->Cells[0]->Value = code;
				dataGridViewUJ->Rows[i]->Cells[1]->Value = officialTitle;
				size_t j = 2;
				for (j; j < item->accessData()->getVzdelavanie().size() + 2; j++)
				{
					int^ number = gcnew int(item->accessData()->getVzdelavanie().at(j - 2));
					dataGridViewUJ->Rows[i]->Cells[j]->Value = number;
				}
				for (size_t k = 0; k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
				{
					int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
					dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
				}

				i++;
			}
		}
		label3->Text = "Vyfiltrované!";
	
}
private: System::Void dataGridView1_CellContentClick_1(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}


private: System::Void dataGridView1_CellContentClick_2(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: void addNewColumn(wstring nameOfFilterP,wstring typeP,wstring fromP, wstring toP) {
	String^ nameOfFilter = gcnew String(nameOfFilterP.c_str());
	String^ type = gcnew String(typeP.c_str());
	String^ from = gcnew String(fromP.c_str());
	String^ to = gcnew String(toP.c_str());
	dataGridView1->Rows->Add();
	dataGridView1->Rows[numberOfColumns]->Cells[0]->Value = nameOfFilter;
	dataGridView1->Rows[numberOfColumns]->Cells[1]->Value = type;
	dataGridView1->Rows[numberOfColumns]->Cells[2]->Value = from;
	dataGridView1->Rows[numberOfColumns]->Cells[3]->Value = to;
	numberOfColumns++;
}
private: System::Void comboBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	dataGridView1->Rows->Clear();
	
	numberOfColumns = 0;
	delete compFilter;
	compFilter = new compositeFilter<uzemnaJednotka*>();
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
