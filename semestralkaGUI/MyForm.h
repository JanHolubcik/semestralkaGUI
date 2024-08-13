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
			filteredValues = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
			UJ = new structures::UnsortedSequenceTable<int, uzemnaJednotka*>();
			criterioName* cByName = new criterioName();
			sorter<int, uzemnaJednotka, wstring>* sortTable = new sorter<int, uzemnaJednotka, wstring>();;

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
			sortTable->sortByName(*sortingTable, cByName, 0);
			int i = 0;
			obce->clear();
			for (auto item : *sortingTable) {
				obce->insert(i, item->accessData());
				i++;
			}
			sortingTable->assign(*okresy);
			sortTable->sortByName(*sortingTable, cByName, 0);
			okresy->clear();
			 i = 0;
			for (auto item : *sortingTable) {
				okresy->insert(i, item->accessData());
				i++;
			}
			sortingTable->assign(*kraje);
			sortTable->sortByName(*sortingTable, cByName, 0);
			kraje->clear();
			 i = 0;
			for (auto item : *sortingTable) {
				kraje->insert(i, item->accessData());
				i++;
			}
			sortingTable->assign(*krajiny);
			sortTable->sortByName(*sortingTable, cByName, 0);
			krajiny->clear();
			 i = 0;
			for (auto item : *sortingTable) {
				krajiny->insert(i, item->accessData());
				i++;
			}
			delete sortingTable;
			delete sortTable;
			delete cByName;
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
			
				delete findByBisection;
				delete filteredValues;
				delete compFilter;
				delete UJ;
				delete valueCrit;
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




	private: System::Windows::Forms::TextBox^ textBoxFind;
	private: System::Windows::Forms::Label^ label2;

	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>* obce = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>* okresy = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>*kraje = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>*krajiny = nullptr;
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>* filteredValues = nullptr; 
	private: structures::UnsortedSequenceTable<int, uzemnaJednotka*>* UJ = nullptr;
	private: structures::ArrayList<int>* valueCrit = new structures::ArrayList<int>();
	private: bisectionName* findByBisection = nullptr;
	private: compositeFilter<uzemnaJednotka*>* compFilter = nullptr;
		   cUJVekovaSkupinaRatio* cVekSkuRa = nullptr;
		   cUJVekovaSkupina* cVekSku = nullptr;
		   cUJVekRatio* cVekRa = nullptr;
		   cUJVekGroupSum* cVekGroup = nullptr;
		   cUJVzdelavanieGroupRatio* cVzdeRa = nullptr;
		   kUJVzdelavanieSum* cVzdeSum = nullptr;
		   cBelongsTo* cBeTo = nullptr;
		   cType* cTy = nullptr;
		   criterioName* cName = nullptr;
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
private: System::Windows::Forms::ComboBox^ comboBox3;
private: System::Windows::Forms::CheckBox^ checkBox3;
private: System::Windows::Forms::ComboBox^ comboBox4;
private: System::Windows::Forms::ComboBox^ comboBox5;
private: System::Windows::Forms::ComboBox^ comboBox6;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::CheckBox^ checkBox4;
private: System::Windows::Forms::TextBox^ textBox3;
private: System::Windows::Forms::TextBox^ textBox4;
private: System::Windows::Forms::Label^ label8;
private: System::Windows::Forms::Label^ label9;
private: System::Windows::Forms::CheckBox^ checkBox5;
private: System::Windows::Forms::Label^ label10;


























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
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewUJ))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(137, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Zvoľ územnú jednotku";
			// 
			// comboBoxUJ
			// 
			this->comboBoxUJ->FormattingEnabled = true;
			this->comboBoxUJ->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Obec", L"Okres", L"Kraj", L"Slovensko" });
			this->comboBoxUJ->Location = System::Drawing::Point(15, 32);
			this->comboBoxUJ->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->comboBoxUJ->Name = L"comboBoxUJ";
			this->comboBoxUJ->Size = System::Drawing::Size(148, 24);
			this->comboBoxUJ->TabIndex = 2;
			this->comboBoxUJ->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxUJ_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 62);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(379, 43);
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
			this->dataGridViewUJ->Location = System::Drawing::Point(35, 267);
			this->dataGridViewUJ->Margin = System::Windows::Forms::Padding(0);
			this->dataGridViewUJ->Name = L"dataGridViewUJ";
			this->dataGridViewUJ->RowHeadersVisible = false;
			this->dataGridViewUJ->RowHeadersWidth = 51;
			this->dataGridViewUJ->RowTemplate->Height = 24;
			this->dataGridViewUJ->Size = System::Drawing::Size(1691, 647);
			this->dataGridViewUJ->TabIndex = 3;
			this->dataGridViewUJ->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellContentClick);
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
			this->Column16->MinimumWidth = 6;
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
			// textBoxFind
			// 
			this->textBoxFind->Location = System::Drawing::Point(173, 34);
			this->textBoxFind->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBoxFind->Name = L"textBoxFind";
			this->textBoxFind->Size = System::Drawing::Size(216, 22);
			this->textBoxFind->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(169, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(91, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Vyhľadávanie";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(778, 16);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(96, 25);
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
			this->comboBox1->Location = System::Drawing::Point(881, 13);
			this->comboBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(276, 24);
			this->comboBox1->TabIndex = 7;
			this->comboBox1->Visible = false;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::showValueFields);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(778, 68);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(185, 22);
			this->textBox1->TabIndex = 8;
			this->textBox1->Visible = false;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(970, 68);
			this->textBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(185, 22);
			this->textBox2->TabIndex = 9;
			this->textBox2->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(778, 44);
			this->checkBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(178, 20);
			this->checkBox1->TabIndex = 10;
			this->checkBox1->Text = L"Filtrovať podla intervalu \?";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->Visible = false;
			this->checkBox1->Click += gcnew System::EventHandler(this, &MyForm::checkBox1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(776, 202);
			this->button3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(379, 39);
			this->button3->TabIndex = 11;
			this->button3->Text = L"Pridaj filter";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(277, 89);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 16);
			this->label3->TabIndex = 12;
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(1173, 203);
			this->button4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(251, 39);
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
			this->comboBox2->Location = System::Drawing::Point(778, 174);
			this->comboBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(377, 24);
			this->comboBox2->TabIndex = 15;
			this->comboBox2->Visible = false;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox2_SelectedIndexChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(1009, 94);
			this->checkBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(129, 20);
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
			this->dataGridView1->Location = System::Drawing::Point(1173, 9);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(0);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(505, 192);
			this->dataGridView1->TabIndex = 17;
			this->dataGridView1->Visible = false;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellContentClick_3);
			// 
			// Column1
			// 
			this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->Column1->HeaderText = L"Filter";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 65;
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
			this->button5->Location = System::Drawing::Point(1431, 203);
			this->button5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(248, 38);
			this->button5->TabIndex = 18;
			this->button5->Text = L"Resetuj filtre";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Visible = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
				L"názov", L"bez ukončeného vzdelania", L"základné vzdelanie ",
					L"stredné odborné vzdelanie", L"úplne stredné vzdelanie", L"vyššie odborné vzdelanie", L"vysokoškolské vzdelanie", L"bez školského vzdelania",
					L"nezistené", L"predproduktívny", L"produktívny", L"postproduktívny"
			});
			this->comboBox3->Location = System::Drawing::Point(395, 35);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(188, 24);
			this->comboBox3->TabIndex = 19;
			this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox3_SelectedIndexChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(400, 65);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(97, 20);
			this->checkBox3->TabIndex = 20;
			this->checkBox3->Text = L"vzostupne\?";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Location = System::Drawing::Point(589, 32);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(169, 24);
			this->comboBox4->TabIndex = 21;
			this->comboBox4->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox4_SelectedIndexChanged);
			// 
			// comboBox5
			// 
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
				L"názov", L"bez ukončeného vzdelania", L"základné vzdelanie ",
					L"stredné odborné vzdelanie", L"úplne stredné vzdelanie", L"vyššie odborné vzdelanie", L"vysokoškolské vzdelanie", L"bez školského vzdelania",
					L"nezistené", L"predproduktívny", L"produktívny", L"postproduktívny"
			});
			this->comboBox5->Location = System::Drawing::Point(400, 132);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(183, 24);
			this->comboBox5->TabIndex = 22;
			this->comboBox5->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox5_SelectedIndexChanged);
			// 
			// comboBox6
			// 
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Location = System::Drawing::Point(589, 132);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(169, 24);
			this->comboBox6->TabIndex = 23;
			this->comboBox6->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox6_SelectedIndexChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(397, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(117, 16);
			this->label4->TabIndex = 24;
			this->label4->Text = L"Triedenie bez filtra";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(586, 7);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(112, 16);
			this->label5->TabIndex = 25;
			this->label5->Text = L"Triedenie z filtrom";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(400, 113);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(164, 16);
			this->label6->TabIndex = 26;
			this->label6->Text = L"Hladanie maxima bez filtra";
			this->label6->Click += gcnew System::EventHandler(this, &MyForm::label6_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(586, 111);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(160, 16);
			this->label7->TabIndex = 27;
			this->label7->Text = L"Hladanie maxima s filtrom\r\n";
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(400, 162);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(133, 20);
			this->checkBox4->TabIndex = 28;
			this->checkBox4->Text = L"Hladať minimum\?";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox4_CheckedChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(778, 134);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 22);
			this->textBox3->TabIndex = 29;
			this->textBox3->Visible = false;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(884, 134);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 22);
			this->textBox4->TabIndex = 30;
			this->textBox4->Visible = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(778, 113);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(23, 16);
			this->label8->TabIndex = 31;
			this->label8->Text = L"od";
			this->label8->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(884, 112);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(23, 16);
			this->label9->TabIndex = 32;
			this->label9->Text = L"do";
			this->label9->Visible = false;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(1009, 119);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(128, 20);
			this->checkBox5->TabIndex = 33;
			this->checkBox5->Text = L"Obidva pohlavia";
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->Visible = false;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(1170, 247);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(96, 16);
			this->label10->TabIndex = 34;
			this->label10->Text = L"Vitaj v aplikácii";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1748, 938);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->checkBox5);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->comboBox6);
			this->Controls->Add(this->comboBox5);
			this->Controls->Add(this->comboBox4);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->comboBox3);
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
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
		int i = 0;
		dataGridViewUJ->Columns->Clear();
		dataGridViewUJ->Rows->Clear();
		dataGridViewUJ->Columns->Add(L"Code", L"Code");
		dataGridViewUJ->Columns->Add(L"Column4", L"Official title");
		dataGridViewUJ->Columns->Add(L"Column16", L"");
		dataGridViewUJ->Columns->Add(L"Column17", L"");
		dataGridViewUJ->Columns->Add(L"Column18", L"");
		dataGridViewUJ->Columns->Add(L"Column5", L"bez ukončeného vzdelania");
		dataGridViewUJ->Columns->Add(L"Column6", L"základné vzdelanie");
		dataGridViewUJ->Columns->Add(L"Column7", L"stredné odborné vzdelanie");
		dataGridViewUJ->Columns->Add(L"Column8", L"úplné stredné vzdelanie");
		dataGridViewUJ->Columns->Add(L"Column9", L"vyššie odborné vzdelanie");
		dataGridViewUJ->Columns->Add(L"Column10", L"vysokoškolské vzdelanie");
		dataGridViewUJ->Columns->Add(L"Column11", L"bez školského vzdelania");
		dataGridViewUJ->Columns->Add(L"Column12", L"nezistené");
		dataGridViewUJ->Columns->Add(L"Column13", L"Predproduktívny");
		dataGridViewUJ->Columns->Add(L"Column14", L"Produktívny");
		dataGridViewUJ->Columns->Add(L"Column15", L"Postproduktívny");
		
	for (auto item : *UJ) {
		dataGridViewUJ->Rows->Add();
		String^ code = gcnew String(item->accessData()->getCode().c_str());
		String^ officialTitle = gcnew String(item->accessData()->getOfficialTitle().c_str());
		dataGridViewUJ->Rows[i]->Cells[0]->Value = code;
		dataGridViewUJ->Rows[i]->Cells[1]->Value = officialTitle;
		int belongsTo = 2;
		uzemnaJednotka* UJPrem = item->accessData()->getBelongsTo();
		while (UJPrem) {

			String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
			dataGridViewUJ->Rows[i]->Cells[belongsTo]->Value = name;
			UJPrem = UJPrem->getBelongsTo();
			belongsTo++;
		}
	
		size_t j = 5;
		for (j ; j < item->accessData()->getVzdelavanie().size()+5; j++)
		{
			int^ number = gcnew int(item->accessData()->getVzdelavanie().at(j-5));
			dataGridViewUJ->Rows[i]->Cells[j]->Value = number;
		}
		for (size_t k=0; k < (item->accessData()->getVekovaSkupina().size()/2); k++)
		{
			int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k+3));
			dataGridViewUJ->Rows[i]->Cells[j+k]->Value = number;
		}
		
		i++;
	}
	



	
}
private: System::Void showFilter(System::Object^ sender, System::EventArgs^ e) {
	comboBox1->Visible = !comboBox1->Visible;
	checkBox1->Visible = !checkBox1->Visible;
	checkBox5->Visible = !checkBox5->Visible;
	button4->Visible = !button4->Visible;
	button3->Visible = !button3->Visible;
	textBox1->Visible = !textBox1->Visible;
	textBox2->Visible = !textBox2->Visible;
	textBox4->Visible = !textBox4->Visible;
	textBox3->Visible = !textBox3->Visible;
	dataGridView1->Visible = !dataGridView1->Visible;
	button5->Visible = !button5->Visible;
	label9->Visible = !label9->Visible;
		label8->Visible = !label8->Visible;
	if (textBox1->Visible || textBox2->Visible) {
		textBox1->Visible = false;
		textBox2->Visible = false;
	}
}
private: System::Void showValueFields(System::Object^ sender, System::EventArgs^ e) {
	textBox1->Visible = false;
	textBox2->Visible = false;
	comboBox2->Visible = false;
	checkBox2->Visible = false;
	checkBox1->Visible = false;
	checkBox5->Visible = false;
	textBox3->Visible = false;
	textBox4->Visible = false;
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
			checkBox2->Visible = true;
			checkBox5->Visible = true;
			textBox3->Visible = true;
			textBox4->Visible = true;
			textBox1->Visible = true;
			if (checkBox1->Checked == true) {
				textBox2->Visible = true;
			}
			break;
		}
		case 6: {
			checkBox1->Visible = true;
			checkBox2->Visible = true;
			checkBox5->Visible = true;
			textBox3->Visible = true;
			textBox4->Visible = true;
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
	String^ textValue3 = gcnew String(textBox3->Text);
	String^ textValue4 = gcnew String(textBox4->Text);
	int value1 = 0;
	int value2 = 0;
	int value3 = 0;
	int value4 = 0;
	double doubleValue1 = 0;
	double doubleValue2 = 0;
	bool isNumber1 = Int32::TryParse(code, value1);
	bool isNumber2 = Int32::TryParse(textValue2, value2);
	bool isdouble1 = Double::TryParse(code, doubleValue1);
	bool isdouble2 = Double::TryParse(textValue2, doubleValue2);
	bool isNumber3 = Int32::TryParse(textValue3, value3);
	bool isNumber4 = Int32::TryParse(textValue4, value4);
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
				cName = new criterioName();
				fUJByValue<std::wstring, uzemnaJednotka*, std::wstring>* filterbyvalue =
					new  fUJByValue<std::wstring, uzemnaJednotka*, std::wstring>(cName, cName->evaluate(&findByBisection->getFoundByBisection()));
				fUJByValue<std::wstring, uzemnaJednotka*, std::wstring>* filterby = filterbyvalue;
				compFilter->addFilter(filterbyvalue);
				label10->Text = "Filter bol úspešne pridaný";
				addNewColumn(L"Podľa hodnoty", cName->evaluate(&findByBisection->getFoundByBisection()), L"", L"");
			//	delete cName;
			//	delete filterbyvalue;
			}
			else {
				label10->Text = "Nenašla sa územná jednotka s názvom: " + code;
			}
			break;
		}
		case 1: {
		
			 cTy = new cType();
			fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue =
				new  fUJByValue<std::wstring, uzemnaJednotka*, int>(cTy, comboBox2->SelectedIndex);
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

					cBeTo = new cBelongsTo(&findByBisection->getFoundByBisection());
					fUJByValue<std::wstring, uzemnaJednotka*, bool>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, bool>(cBeTo, true);
					addNewColumn(L"Podľa príslušnosti", msclr::interop::marshal_as<wstring>(code), L"", L"");
					compFilter->addFilter(filterbyvalue);
					label10->Text = "Filter bol úspešne pridaný";
				}
				else {
					label10->Text = "Nenašla sa územná jednotka s názvom: " + code;
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
							cVzdeSum = new kUJVzdelavanieSum(comboBox2->SelectedIndex);

							filterByInterval<std::wstring, uzemnaJednotka*, int>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, int>(cVzdeSum, value1, value2);
							addNewColumn(L"Vzdelavania", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label10->Text = "Filter bol úspešne pridaný";
						}
						else {
							label10->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label10->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if(isNumber1){
					cVzdeSum = new kUJVzdelavanieSum(comboBox2->SelectedIndex);
					fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, int>(cVzdeSum, value1);
					addNewColumn(L"Vzdelavania", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code), L"");
					compFilter->addFilter(filterbyvalue);
					label10->Text = "Filter bol úspešne pridaný";
					}
					else {
						label10->Text = "Hodnota v poli nie je číslo.";
					}
				}		
			}
			else {
				label10->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		case 4: {
			if (!code->IsNullOrEmpty(code)) {
				if (checkBox1->Checked) {
					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isdouble1 && isdouble2) {
							 cVzdeRa = new cUJVzdelavanieGroupRatio(comboBox2->SelectedIndex);
							filterByInterval<std::wstring, uzemnaJednotka*, double>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, double>(cVzdeRa, doubleValue1, doubleValue2);
							addNewColumn(L"Vzdelavania podiel", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code +" " + textValue2), msclr::interop::marshal_as<wstring>(textValue3+" "+textValue4));
							compFilter->addFilter(filter);
							label10->Text = "Filter bol úspešne pridaný";
						}
						else {
							label10->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label10->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isdouble1) {
						cVzdeRa = new cUJVzdelavanieGroupRatio(comboBox2->SelectedIndex);
						fUJByValue<std::wstring, uzemnaJednotka*, double>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, double>(cVzdeRa, doubleValue1);
						addNewColumn(L"Vzdelavania podiel", msclr::interop::marshal_as<wstring>(comboBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue3 + " " + textValue4));
						compFilter->addFilter(filterbyvalue);
						label10->Text = "Filter bol úspešne pridaný";
					} 
					else {
						label10->Text = "Hodnota v poli nie je číslo.";
					}
				}
			}
			else {
				label10->Text = "Vyhľadavacie pole je prázdne!";
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
				if (checkBox5->Checked)
				{
					pohlavie = -1;
				}
				if (checkBox1->Checked) {
					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isNumber1 && isNumber2 && isNumber3 && isNumber4) {
							cVekGroup = new cUJVekGroupSum(pohlavie, value3, value4);
							
							filterByInterval<std::wstring, uzemnaJednotka*, int>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, int>
								(cVekGroup, value1, value2);
							addNewColumn(L"Vek", checkBox5->Checked?L"Obidva" : (checkBox2->Checked?L"Žena" :L"Muž"), msclr::interop::marshal_as<wstring>(code+" "+ textValue2), msclr::interop::marshal_as<wstring>(value3+" "+value4));
							compFilter->addFilter(filter);
							label10->Text = "Filter bol úspešne pridaný";
						}
						else {
							label10->Text = "Zadaj čísla do všetkých polí.";
						}
					}
					else {
						label10->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isNumber1 && isNumber3 && isNumber4) {
						cVekGroup = new cUJVekGroupSum(pohlavie, value3, value4);
						fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, int>(cVekGroup, value1);
						addNewColumn(L"Vek", checkBox5->Checked ? L"Obidva" : (checkBox2->Checked ? L"Žena" : L"Muž"), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(value3 + " " + value4));
						compFilter->addFilter(filterbyvalue);
						label10->Text = "Filter bol úspešne pridaný";
					}
					else {
						label10->Text = "Zadaj čísla do všetkých polí.";
					}
				}
			}
			else {
				label10->Text = "Vyhľadavacie pole je prázdne!";
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
				if (checkBox5->Checked)
				{
					pohlavie = -1;
				}
				if (checkBox1->Checked) {
					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isdouble1 && isdouble2 && isNumber3 && isNumber4) {
						cVekRa = new cUJVekRatio(pohlavie,value3,value4);
						
						filterByInterval<std::wstring, uzemnaJednotka*, double>* filter =
							new  filterByInterval<std::wstring, uzemnaJednotka*, double>(cVekRa, doubleValue1, doubleValue2);
						addNewColumn(L"Vek podiel", checkBox5->Checked ? L"Obidva" : (checkBox2->Checked ? L"Žena" : L"Muž"), msclr::interop::marshal_as<wstring>(code+" "+textValue2), msclr::interop::marshal_as<wstring>(value3 + " " + value4));
						compFilter->addFilter(filter);
						label10->Text = "Filter bol úspešne pridaný";
						}
						else {
							label10->Text = "Zadaj čísla do všetkých polí.";
						}
					}
					else {
						label10->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isdouble1 && isNumber3 && isNumber4){
						cVekRa = new cUJVekRatio(pohlavie, value3, value4);
					fUJByValue<std::wstring, uzemnaJednotka*, double>* filterbyvalue = 
						new  fUJByValue<std::wstring, uzemnaJednotka*, double>(cVekRa, doubleValue1);
					addNewColumn(L"Vek podiel", checkBox5->Checked ? L"Obidva" : (checkBox2->Checked ? L"Žena" : L"Muž"), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(value3 + " " + value4));
					compFilter->addFilter(filterbyvalue);
					
					label10->Text = "Filter bol úspešne pridaný";
					}
					else {
						label10->Text = "Hodnota v poli nie je číslo.";
					}
				}
			}
			else {
				label10->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		case 7: {
			if (!code->IsNullOrEmpty(code)) {
				if (checkBox1->Checked) {
					if (isNumber1 && isNumber2) {
						if (!textValue2->IsNullOrEmpty(textValue2))
						{
							cVekSku = new cUJVekovaSkupina(comboBox2->SelectedIndex);
							filterByInterval<std::wstring, uzemnaJednotka*, int>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, int>
								(cVekSku, value1, value2);
							addNewColumn(L"Vek skupina", msclr::interop::marshal_as<wstring>(checkBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label10->Text = "Filter bol úspešne pridaný";
						}
						else {
							label10->Text = "Pre interval treba vyplniť aj druhé pole!";
						}
					}
					else {
						label10->Text = "Obidve alebo len jedna hodnota nie je číslo.";
					}
				}
				else {
					if (isNumber1) {
						cVekSku = new cUJVekovaSkupina(comboBox2->SelectedIndex);
						fUJByValue<std::wstring, uzemnaJednotka*, int>* filterbyvalue =
							new  fUJByValue<std::wstring, uzemnaJednotka*, int>(cVekSku, value1);
						addNewColumn(L"Vek skupina", msclr::interop::marshal_as<wstring>(checkBox2->Text), msclr::interop::marshal_as<wstring>(code), L"");
						compFilter->addFilter(filterbyvalue);
						label10->Text = "Filter bol úspešne pridaný";
					}
					else {
						label10->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
			}
			else {
				label10->Text = "Hodnota v poli nie je číslo.";
			}
			break;
		}
		default: {
			if (!code->IsNullOrEmpty(code)) {

				if (checkBox1->Checked) {

					if (!textValue2->IsNullOrEmpty(textValue2))
					{
						if (isdouble1 && isdouble2) {
							cVekSkuRa = new cUJVekovaSkupinaRatio(comboBox2->SelectedIndex);
							filterByInterval<std::wstring, uzemnaJednotka*, double>* filter =
								new  filterByInterval<std::wstring, uzemnaJednotka*, double>(cVekSkuRa, doubleValue1, doubleValue2);
							addNewColumn(L"Vek skupina podiel", msclr::interop::marshal_as<wstring>(checkBox2->Text), msclr::interop::marshal_as<wstring>(code), msclr::interop::marshal_as<wstring>(textValue2));
							compFilter->addFilter(filter);
							label10->Text = "Filter bol úspešne pridaný";
						}
						else {
							label10->Text = "Obidve alebo len jedna hodnota nie je číslo.";
						}
					}
					else {
						label10->Text = "Pre interval treba vyplniť aj druhé pole!";
					}
				}
				else {
					if (isdouble1){
						cVekSkuRa = new cUJVekovaSkupinaRatio(comboBox2->SelectedIndex);
					fUJByValue<std::wstring, uzemnaJednotka*, double>* filterbyvalue = new  fUJByValue<std::wstring, uzemnaJednotka*, double>(cVekSkuRa, doubleValue1);
					addNewColumn(L"Vek skupina podiel", msclr::interop::marshal_as<wstring>(comboBox2->Text), L"", L"");
					compFilter->addFilter(filterbyvalue);
					label10->Text = "Filter bol úspešne pridaný";
					}
					else {
						label10->Text = "Hodnota v poli nie je číslo.";
					}
				}
			}
			else {
				label10->Text = "Vyhľadavacie pole je prázdne!";
			}
			break;
		}
		}
	//}

}
private: System::Void filterUJ(System::Object^ sender, System::EventArgs^ e) {
	label10->Text = "Filtruje sa!";
	UJ->clear();
	dataGridViewUJ->Rows->Clear();
	dataGridViewUJ->Columns->Clear();
	dataGridViewUJ->Columns->Add(L"Code", L"Code");
	dataGridViewUJ->Columns->Add(L"Column4", L"Official title");
	dataGridViewUJ->Columns->Add(L"Column5", L"bez ukončeného vzdelania");
	dataGridViewUJ->Columns->Add(L"Column6", L"základné vzdelanie");
	dataGridViewUJ->Columns->Add(L"Column7", L"stredné odborné vzdelanie");
	dataGridViewUJ->Columns->Add(L"Column8", L"úplné stredné vzdelanie");
	dataGridViewUJ->Columns->Add(L"Column9", L"vyššie odborné vzdelanie");
	dataGridViewUJ->Columns->Add(L"Column10", L"vysokoškolské vzdelanie");
	dataGridViewUJ->Columns->Add(L"Column11", L"bez školského vzdelania");
	dataGridViewUJ->Columns->Add(L"Column12", L"nezistené");
	dataGridViewUJ->Columns->Add(L"Column13", L"Predproduktívny");
	dataGridViewUJ->Columns->Add(L"Column14", L"Produktívny");
	dataGridViewUJ->Columns->Add(L"Column15", L"Postproduktívny");
	
	int k = 0;
	int j = 0;
	if (cVekSkuRa) {
		bool itemExists = false;
		if(!comboBox4->Items->Contains(L"Vek skupina podiel")) {
		dataGridViewUJ->Columns->Add(L"Column15", L"Vek skupina podiel");
		valueCrit->add(k);
		comboBox4->Items->Insert(j, L"Vek skupina podiel");
		comboBox6->Items->Insert(j, L"Vek skupina podiel");
		
		}
		j++;
	}
	k++;
	if (cVekSku) {
		if (!comboBox4->Items->Contains(L"Vek skupina")) {
			dataGridViewUJ->Columns->Add(L"Column16", L"Vek skupina");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Vek skupina");
			comboBox6->Items->Insert(j, L"Vek skupina");
		}
		j++;
	}
	k++;
	if (cVekRa) {
		if (!comboBox4->Items->Contains(L"Vek podiel")) {
			dataGridViewUJ->Columns->Add(L"Column17", L"Vek podiel");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Vek podiel");
			comboBox6->Items->Insert(j, L"Vek podiel");
		}
		j++;
	}
	k++;
	if (cVekGroup) {
		if (!comboBox4->Items->Contains(L"Vek")) {
			dataGridViewUJ->Columns->Add(L"Column18", L"vek");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Vek");
			comboBox6->Items->Insert(j, L"Vek");
		}
		j++;
	}
	k++;
	if (cVzdeRa) {
		if (!comboBox4->Items->Contains(L"Vzdelavanie podiel")) {
			dataGridViewUJ->Columns->Add(L"Column19", L"Vzdelavanie podiel");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Vzdelavanie podiel");
			comboBox6->Items->Insert(j, L"Vzdelavanie podiel");
		}
		j++;
	}
	k++;

	if (cVzdeSum) {
		
		if (!comboBox4->Items->Contains(L"Vzdelavanie")) {
			dataGridViewUJ->Columns->Add(L"Column21", L"Vzdelavanie");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Vzdelavanie");
			comboBox6->Items->Insert(j, L"Vzdelavanie");
		}
		j++;
	}
	k++;
	if (cBeTo) {
		if (!comboBox4->Items->Contains(L"Patrí k")) {
			dataGridViewUJ->Columns->Add(L"Column20", L"Patrí k");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Patrí k");
			comboBox6->Items->Insert(j, L"Patrí k");		
		}
		j++;
	}

	k++;
	if (cTy) {
		if (!comboBox4->Items->Contains(L"Typ")) {
			dataGridViewUJ->Columns->Add(L"Column22", L"Typ");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Typ");
			comboBox6->Items->Insert(j, L"Typ");
		}
		j++;
	
	}
	k++;
	if (cName) {
		if (!comboBox4->Items->Contains(L"Meno")) {
			dataGridViewUJ->Columns->Add(L"Column23", L"Meno");
			valueCrit->add(k);
			comboBox4->Items->Insert(j, L"Meno");
			comboBox6->Items->Insert(j, L"Meno");
		}
		j++;
	}

	dataGridViewUJ->Columns->Add(L"Column24", L"");
	dataGridViewUJ->Columns->Add(L"Column25", L"");
	dataGridViewUJ->Columns->Add(L"Column26", L"");
	dataGridViewUJ->Columns->Add(L"Column27", L"");
	dataGridViewUJ->Columns->Add(L"Column28", L"");
	dataGridViewUJ->Columns->Add(L"Column29", L"");
	int i = 0;
	for (auto item : *obce) {
		if(compFilter->matchesFilterAnd(item->accessData())){
		UJ->insert(i, item->accessData());
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
		size_t k = 0;
		for (k; k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
		{
			int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
			dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
		}
		size_t l = 0;
		for (l ; l < valueCrit->size(); l++)
		{
			switch (valueCrit->at(l)) {
			case 0: {
				double^ value = gcnew double(cVekSkuRa->evaluate(item->accessData()));
				dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				break;
			}
			case 1: {
				int^ value = gcnew int(cVekSku->evaluate(item->accessData()));
				dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				break;
			}
			case 2: {
				double^ value = gcnew double(cVekRa->evaluate(item->accessData()));
				dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				break;
			}
			case 3: {
				int^ value = gcnew int(cVekGroup->evaluate(item->accessData()));
				dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				break;
			}
			case 4: {
				double^ value = gcnew double(cVzdeRa->evaluate(item->accessData()));
				dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				break;
			}
			case 5: {
				int^ value = gcnew int(cVzdeSum->evaluate(item->accessData()));
				dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				break;
			}
			case 6: {
				if (cBeTo->evaluate(item->accessData())) {
						String^ officialTitle = gcnew String(item->accessData()->getBelongsTo()->getOfficialTitle().c_str());
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = officialTitle;
				}
				break;
			}
			case 7: {
				int value = cTy->evaluate(item->accessData());
				switch (value)
				{
				case 0: {
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Obec";
					break;
					}
					case 1: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Okres";
						break;
					}
					case 2: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Kraje";
						break;
					}
					case 3: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Slovensko";
						break;
					}
				default:
					break;
				}
				break;
			}
		
			default: {
				String^ value = gcnew String(cName->evaluate(item->accessData()).c_str());
				dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
			}
			}
		}
		int belongsTo = j + k + l;
		uzemnaJednotka* UJPrem = item->accessData()->getBelongsTo();
		while (UJPrem) {

			String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
			dataGridViewUJ->Rows[i]->Cells[belongsTo]->Value = name;
			UJPrem = UJPrem->getBelongsTo();
			belongsTo++;
		}
		
		i++;
		}
	}
	for (auto item : *okresy) {
		if (compFilter->matchesFilterAnd(item->accessData())) {
			UJ->insert(i, item->accessData());
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
			size_t k = 0;
			for (k; k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
			{
				int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
				dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
			}
			size_t l = 0;
			for (l; l < valueCrit->size(); l++)
			{
				switch (valueCrit->at(l)) {
				case 0: {
					double^ value = gcnew double(cVekSkuRa->evaluate(item->accessData()));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 1: {
					int^ value = gcnew int(cVekSku->evaluate(item->accessData()));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 2: {
					double^ value = gcnew double(cVekRa->evaluate(item->accessData()));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 3: {
					int^ value = gcnew int(cVekGroup->evaluate(item->accessData()));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 4: {
					double^ value = gcnew double(cVzdeRa->evaluate(item->accessData()));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 5: {
					int^ value = gcnew int(cVzdeSum->evaluate(item->accessData()));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 6: {
					if (cBeTo->evaluate(item->accessData())) {
						String^ officialTitle = gcnew String(item->accessData()->getBelongsTo()->getOfficialTitle().c_str());
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = officialTitle;
					}
					break;
				}
				case 7: {
					int value = cTy->evaluate(item->accessData());
					switch (value)
					{
					case 0: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Obec";
						break;
					}
					case 1: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Okres";
						break;
					}
					case 2: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Kraje";
						break;
					}
					case 3: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Slovensko";
						break;
					}
					default:
						break;
					}
					break;
				}

				default: {
					String^ value = gcnew String(cName->evaluate(item->accessData()).c_str());
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				}
				}
			}
			int belongsTo = j +k+ l;
			uzemnaJednotka* UJPrem = item->accessData()->getBelongsTo();
			while (UJPrem) {

				String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
				dataGridViewUJ->Rows[i]->Cells[belongsTo]->Value = name;
				UJPrem = UJPrem->getBelongsTo();
				belongsTo++;
			}
			i++;
		}
	}
		for (auto item : *kraje) {
			if (compFilter->matchesFilterAnd(item->accessData())) {
				UJ->insert(i, item->accessData());
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
				size_t k = 0;
				for (k ; k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
				{
					int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
					dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
				}
				size_t l = 0;
				for ( l ; l < valueCrit->size(); l++)
				{
					switch (valueCrit->at(l)) {
					case 0: {
						double^ value = gcnew double(cVekSkuRa->evaluate(item->accessData()));
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
						break;
					}
					case 1: {
						int^ value = gcnew int(cVekSku->evaluate(item->accessData()));
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
						break;
					}
					case 2: {
						double^ value = gcnew double(cVekRa->evaluate(item->accessData()));
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
						break;
					}
					case 3: {
						int^ value = gcnew int(cVekGroup->evaluate(item->accessData()));
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
						break;
					}
					case 4: {
						double^ value = gcnew double(cVzdeRa->evaluate(item->accessData()));
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
						break;
					}
					case 5: {
						int^ value = gcnew int(cVzdeSum->evaluate(item->accessData()));
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
						break;
					}
					case 6: {
						if (cBeTo->evaluate(item->accessData())) {
							String^ officialTitle = gcnew String(item->accessData()->getBelongsTo()->getOfficialTitle().c_str());
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = officialTitle;
						}
						break;
					}
					case 7: {
						int value = cTy->evaluate(item->accessData());
						switch (value)
						{
						case 0: {
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Obec";
							break;
						}
						case 1: {
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Okres";
							break;
						}
						case 2: {
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Kraje";
							break;
						}
						case 3: {
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Slovensko";
							break;
						}
						default:
							break;
						}
						break;
					}

					default: {
						String^ value = gcnew String(cName->evaluate(item->accessData()).c_str());
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					}
					}
				}
				int belongsTo = j + k + l;
				uzemnaJednotka* UJPrem = item->accessData()->getBelongsTo();
				while (UJPrem) {

					String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
					dataGridViewUJ->Rows[i]->Cells[belongsTo]->Value = name;
					UJPrem = UJPrem->getBelongsTo();
					belongsTo++;
				}
				i++;
			}
		}
		label10->Text = "Vyfiltrované!";
	
	
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
	valueCrit->clear();
	comboBox4->Items->Clear();
	comboBox6->Items->Clear();
	 cVekSkuRa = nullptr;
	 cVekSku = nullptr;
	 cVekRa = nullptr;
	 cVekGroup = nullptr;
	 cVzdeRa = nullptr;
	 cVzdeSum = nullptr;
	 cBeTo = nullptr;
	 cTy = nullptr;
	 cName = nullptr;
	compFilter = new compositeFilter<uzemnaJednotka*>();
}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void dataGridView1_CellContentClick_3(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: System::Void comboBox3_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	switch (comboBox3->SelectedIndex) {
	case 0:{
		criterioName* fiName = new criterioName();
		sorter<int, uzemnaJednotka, wstring>* sortTable = new sorter<int, uzemnaJednotka, wstring>();
		sortTable->sortByName(*UJ, fiName, checkBox3->Checked ? 1 : 0);
		delete fiName;
		delete sortTable;
		break;
	}
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8: {
		kUJVzdelavanieSum* cFilterVz = new kUJVzdelavanieSum(comboBox3->SelectedIndex-1);
		sorter<int, uzemnaJednotka, int>* sortTable = new sorter<int, uzemnaJednotka, int>();
		sortTable->sortByName(*UJ, cFilterVz, checkBox3->Checked ? 1 : 0);
		delete cFilterVz;
		delete sortTable;
		break;
	}
	case 9:
	case 10:
	case 11:{
		cUJVekovaSkupina* cFiVek = new cUJVekovaSkupina(comboBox3->SelectedIndex-9);
		sorter<int, uzemnaJednotka, int>* sortTable = new sorter<int, uzemnaJednotka, int>();
		sortTable->sortByName(*UJ, cFiVek, checkBox3->Checked ? 1 : 0);
		delete cFiVek;
		delete sortTable;
		break;
	}
	}
	int i = 0;
	dataGridViewUJ->Rows->Clear();

	for (auto item : *UJ) {
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
		size_t k = 0;
		for ( k;k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
		{
			int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
			dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
		}
		int belongsTo = j + k;
		uzemnaJednotka* UJPrem = item->accessData()->getBelongsTo();
		while (UJPrem) {

			String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
			dataGridViewUJ->Rows[i]->Cells[belongsTo]->Value = name;
			UJPrem = UJPrem->getBelongsTo();
			belongsTo++;
		}
		i++;
		
	}
}
private: System::Void comboBox4_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			switch (valueCrit->at(comboBox4->SelectedIndex)) {
					case 0: {
						sorter<int, uzemnaJednotka, double>* sortTable = new sorter<int, uzemnaJednotka, double>();
						sortTable->sortByName(*UJ, cVekSkuRa, checkBox3->Checked? 1 : 0);
						delete sortTable;
						break;
					}
					case 1: {
						sorter<int, uzemnaJednotka, int>* sortTable = new sorter<int, uzemnaJednotka, int>();
						sortTable->sortByName(*UJ, cVekSku, checkBox3->Checked ? 1 : 0);
						delete sortTable;
						break;
					}
					case 2: {
						sorter<int, uzemnaJednotka, double>* sortTable = new sorter<int, uzemnaJednotka, double>();
						sortTable->sortByName(*UJ, cVekRa, checkBox3->Checked ? 1 : 0);
						delete sortTable;
						break;
					}
					case 3: {
						sorter<int, uzemnaJednotka, int>* sortTable = new sorter<int, uzemnaJednotka, int>();
						sortTable->sortByName(*UJ, cVekGroup, checkBox3->Checked ? 1 : 0);
						delete sortTable;
						break;
					}
					case 4: {
						
						sorter<int, uzemnaJednotka, double>* sortTable = new sorter<int, uzemnaJednotka, double>();
						sortTable->sortByName(*UJ, cVzdeRa, checkBox3->Checked ? 1 : 0);
						delete sortTable;
						break;
					}
					case 5: {
						
						sorter<int, uzemnaJednotka, int>* sortTable = new sorter<int, uzemnaJednotka, int>();
						sortTable->sortByName(*UJ, cVzdeSum, checkBox3->Checked ? 1 : 0);
						delete sortTable;
						break;
					}
					case 6: {					
						sorter<int, uzemnaJednotka, int>* sortTable = new sorter<int, uzemnaJednotka, int>();
						sortTable->sortByName(*UJ, cTy, checkBox3->Checked ? 1 : 0);
						break;
					}
					case 7: {
						
						sorter<int, uzemnaJednotka, int>* sortTable = new sorter<int, uzemnaJednotka, int>();
						sortTable->sortByName(*UJ, cTy, checkBox3->Checked ? 1 : 0);
						delete sortTable;
						break;
					}

					default: {
						sorter<int, uzemnaJednotka, wstring>* sortTable = new sorter<int, uzemnaJednotka, wstring>();
						sortTable->sortByName(*UJ, cName, checkBox3->Checked ? 1 : 0);
						delete sortTable;
					}
					}
			int i = 0;
			dataGridViewUJ->Rows->Clear();
			for (auto item : *UJ) {
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
					size_t k = 0;
					for (k; k < (item->accessData()->getVekovaSkupina().size() / 2); k++)
					{
						int^ number = gcnew int(item->accessData()->getVekovaSkupina().at(k) + item->accessData()->getVekovaSkupina().at(k + 3));
						dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
					}
					size_t l = 0;
					for (l; l < valueCrit->size(); l++)
					{
						switch (valueCrit->at(l)) {
						case 0: {
							double^ value = gcnew double(cVekSkuRa->evaluate(item->accessData()));
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
							break;
						}
						case 1: {
							int^ value = gcnew int(cVekSku->evaluate(item->accessData()));
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
							break;
						}
						case 2: {
							double^ value = gcnew double(cVekRa->evaluate(item->accessData()));
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
							break;
						}
						case 3: {
							int^ value = gcnew int(cVekGroup->evaluate(item->accessData()));
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
							break;
						}
						case 4: {
							double^ value = gcnew double(cVzdeRa->evaluate(item->accessData()));
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
							break;
						}
						case 5: {
							int^ value = gcnew int(cVzdeSum->evaluate(item->accessData()));
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
							break;
						}
						case 6: {
							if (cBeTo->evaluate(item->accessData())) {
								String^ officialTitle = gcnew String(item->accessData()->getBelongsTo()->getOfficialTitle().c_str());
								dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = officialTitle;
							}
							break;
						}
						case 7: {
							int value = cTy->evaluate(item->accessData());
							switch (value)
							{
							case 0: {
								dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Obec";
								break;
							}
							case 1: {
								dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Okres";
								break;
							}
							case 2: {
								dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Kraje";
								break;
							}
							case 3: {
								dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Slovensko";
								break;
							}
							default:
								break;
							}
							break;
						}

						default: {
							String^ value = gcnew String(cName->evaluate(item->accessData()).c_str());
							dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
						}
						}
					}
					int belongsTo = j + k + l;
					uzemnaJednotka* UJPrem = item->accessData()->getBelongsTo();
					while (UJPrem) {

						String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
						dataGridViewUJ->Rows[i]->Cells[belongsTo]->Value = name;
						UJPrem = UJPrem->getBelongsTo();
						belongsTo++;
					}
					i++;
				
				}
			}
}
private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void comboBox5_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	uzemnaJednotka* findValue = nullptr;
	bool findMinimum = checkBox4->Checked;
	switch (comboBox5->SelectedIndex) {
	case 0: {
		criterioName* fiName = new criterioName();
		 findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (fiName->evaluate(findValue) > fiName->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (fiName->evaluate(findValue) < fiName->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
	
		delete fiName;
		
		break;
	}
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8: {

		kUJVzdelavanieSum* cFilterVz = new kUJVzdelavanieSum(comboBox5->SelectedIndex - 1);
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				int xd = cFilterVz->evaluate(findValue);
				int xdd = cFilterVz->evaluate(item->accessData());
				if (cFilterVz->evaluate(findValue) > cFilterVz->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cFilterVz->evaluate(findValue) < cFilterVz->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		delete cFilterVz;
		break;
	}
	case 9:
	case 10:
	case 11: {
		cUJVekovaSkupina* cFiVek = new cUJVekovaSkupina(comboBox5->SelectedIndex - 9);
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cFiVek->evaluate(findValue) > cFiVek->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cFiVek->evaluate(findValue) < cFiVek->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		delete cFiVek;
	
		break;
	}
	}
	dataGridViewUJ->Rows->Clear();
	dataGridViewUJ->Rows->Add();
	String^ code = gcnew String(findValue->getCode().c_str());
	String^ officialTitle = gcnew String(findValue->getOfficialTitle().c_str());
	dataGridViewUJ->Rows[0]->Cells[0]->Value = code;
	dataGridViewUJ->Rows[0]->Cells[1]->Value = officialTitle;
	size_t j = 2;
	for (j; j < findValue->getVzdelavanie().size() + 2; j++)
	{
		int^ number = gcnew int(findValue->getVzdelavanie().at(j - 2));
		dataGridViewUJ->Rows[0]->Cells[j]->Value = number;
	}
	size_t k = 0;
	for ( k; k < (findValue->getVekovaSkupina().size() / 2); k++)
	{
		int^ number = gcnew int(findValue->getVekovaSkupina().at(k) + findValue->getVekovaSkupina().at(k + 3));
		dataGridViewUJ->Rows[0]->Cells[j + k]->Value = number;
	}
	int belongsTo = j + k;
	uzemnaJednotka* UJPrem = findValue->getBelongsTo();
	while (UJPrem) {

		String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
		dataGridViewUJ->Rows[0]->Cells[belongsTo]->Value = name;
		UJPrem = UJPrem->getBelongsTo();
		belongsTo++;
	}

}
private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void comboBox6_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	uzemnaJednotka* findValue = nullptr;
	bool findMinimum = checkBox4->Checked;
	switch (valueCrit->at(comboBox6->SelectedIndex)) {
	case 0: {
		
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cVekSkuRa->evaluate(findValue) > cVekSkuRa->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cVekSkuRa->evaluate(findValue) < cVekSkuRa->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}

		break;
	}
	case 1: {
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cVekSku->evaluate(findValue) > cVekSku->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cVekSku->evaluate(findValue) < cVekSku->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}

		break;
	}
	case 2: {
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cVekRa->evaluate(findValue) > cVekRa->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cVekRa->evaluate(findValue) < cVekRa->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}

		break;
	}
	case 3: {
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cVekGroup->evaluate(findValue) > cVekGroup->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cVekGroup->evaluate(findValue) < cVekGroup->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}

		break;
	}
	case 4: {
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cVzdeRa->evaluate(findValue) > cVzdeRa->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cVzdeRa->evaluate(findValue) < cVzdeRa->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}

		break;
	}
	case 5: {
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cVzdeSum->evaluate(findValue) > cVzdeSum->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cVzdeSum->evaluate(findValue) < cVzdeSum->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}

		break;
	}
	case 6: {
		
			findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cBeTo->evaluate(findValue) > cBeTo->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cBeTo->evaluate(findValue) < cBeTo->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		};
	}
	case 7: {
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cTy->evaluate(findValue) > cTy->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cTy->evaluate(findValue) < cTy->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		};

		break;
	}

	default: {
		findValue = UJ->find(0);
		if (findMinimum) {
			for (auto item : *UJ) {
				if (cName->evaluate(findValue) > cName->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		}
		else {
			for (auto item : *UJ) {
				if (cName->evaluate(findValue) < cName->evaluate(item->accessData())) {
					findValue = item->accessData();
				}
			}
		};

	}
	}
	int i = 0;
	dataGridViewUJ->Rows->Clear();
	
			dataGridViewUJ->Rows->Add();
			String^ code = gcnew String(findValue->getCode().c_str());
			String^ officialTitle = gcnew String(findValue->getOfficialTitle().c_str());
			dataGridViewUJ->Rows[i]->Cells[0]->Value = code;
			dataGridViewUJ->Rows[i]->Cells[1]->Value = officialTitle;
			size_t j = 2;
			for (j; j < findValue->getVzdelavanie().size() + 2; j++)
			{
				int^ number = gcnew int(findValue->getVzdelavanie().at(j - 2));
				dataGridViewUJ->Rows[i]->Cells[j]->Value = number;
			}
			size_t k = 0;
			for (k; k < (findValue->getVekovaSkupina().size() / 2); k++)
			{
				int^ number = gcnew int(findValue->getVekovaSkupina().at(k) + findValue->getVekovaSkupina().at(k + 3));
				dataGridViewUJ->Rows[i]->Cells[j + k]->Value = number;
			}
			size_t l = 0;
			for (l; l < valueCrit->size(); l++)
			{
				switch (valueCrit->at(l)) {
				case 0: {
					double^ value = gcnew double(cVekSkuRa->evaluate(findValue));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 1: {
					int^ value = gcnew int(cVekSku->evaluate(findValue));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 2: {
					double^ value = gcnew double(cVekRa->evaluate(findValue));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 3: {
					int^ value = gcnew int(cVekGroup->evaluate(findValue));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 4: {
					double^ value = gcnew double(cVzdeRa->evaluate(findValue));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 5: {
					int^ value = gcnew int(cVzdeSum->evaluate(findValue));
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
					break;
				}
				case 6: {
					if (cBeTo->evaluate(findValue)) {
						String^ officialTitle = gcnew String(findValue->getBelongsTo()->getOfficialTitle().c_str());
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = officialTitle;
					}
					break;
				}
				case 7: {
					int value = cTy->evaluate(findValue);
					switch (value)
					{
					case 0: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Obec";
						break;
					}
					case 1: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Okres";
						break;
					}
					case 2: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Kraje";
						break;
					}
					case 3: {
						dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = L"Slovensko";
						break;
					}
					default:
						break;
					}
					break;
				}

				default: {
					String^ value = gcnew String(cName->evaluate(findValue).c_str());
					dataGridViewUJ->Rows[i]->Cells[j + k + l]->Value = value;
				}
				}
			
			}
			int belongsTo = j + k + l;
			uzemnaJednotka* UJPrem = findValue->getBelongsTo();
			while (UJPrem) {

				String^ name = gcnew String(UJPrem->getOfficialTitle().c_str());
				dataGridViewUJ->Rows[0]->Cells[belongsTo]->Value = name;
				UJPrem = UJPrem->getBelongsTo();
				belongsTo++;
			}
		
	


}
};
}
