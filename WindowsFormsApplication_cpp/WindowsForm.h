#pragma once
#include"DataManager.h"
#include"DotNetUtilities.h"
#include"Processor.h"

namespace WindowsFormsApplication_cpp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// WindowsForm ���K�n
	/// </summary>
	public ref class WindowsForm : public System::Windows::Forms::Form
	{
	public:
		WindowsForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();
			lastInputLength = -1;
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~WindowsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^  FileToolStripMenuItem;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::ToolStripMenuItem^  LoadVectorToolStripMenuItem;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Label^  OutputLabel;
	private: System::Windows::Forms::TextBox^  Output;

	private: System::Windows::Forms::Label^  InputLabel;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::Label^  VectorLabel;
	private: System::Windows::Forms::ListBox^  VectorList;
	protected:

	private:
		/// <summary>
		DataManager* dataManager;
		String^ userInput;
		int lastInputLength;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
			 /// </summary>
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
			 /// �o�Ӥ�k�����e�C
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
				 this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->LoadVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
				 this->InputLabel = (gcnew System::Windows::Forms::Label());
				 this->Input = (gcnew System::Windows::Forms::TextBox());
				 this->VectorLabel = (gcnew System::Windows::Forms::Label());
				 this->VectorList = (gcnew System::Windows::Forms::ListBox());
				 this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
				 this->OutputLabel = (gcnew System::Windows::Forms::Label());
				 this->Output = (gcnew System::Windows::Forms::TextBox());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
				 this->menuStrip2->SuspendLayout();
				 this->tableLayoutPanel1->SuspendLayout();
				 this->flowLayoutPanel1->SuspendLayout();
				 this->flowLayoutPanel2->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // menuStrip2
				 // 
				 this->menuStrip2->ImageScalingSize = System::Drawing::Size(20, 20);
				 this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->FileToolStripMenuItem });
				 this->menuStrip2->Location = System::Drawing::Point(0, 0);
				 this->menuStrip2->Name = L"menuStrip2";
				 this->menuStrip2->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
				 this->menuStrip2->Size = System::Drawing::Size(512, 27);
				 this->menuStrip2->TabIndex = 1;
				 this->menuStrip2->Text = L"menuStrip2";
				 // 
				 // FileToolStripMenuItem
				 // 
				 this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->LoadVectorToolStripMenuItem });
				 this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
				 this->FileToolStripMenuItem->Size = System::Drawing::Size(45, 23);
				 this->FileToolStripMenuItem->Text = L"File";
				 // 
				 // LoadVectorToolStripMenuItem
				 // 
				 this->LoadVectorToolStripMenuItem->Name = L"LoadVectorToolStripMenuItem";
				 this->LoadVectorToolStripMenuItem->Size = System::Drawing::Size(168, 26);
				 this->LoadVectorToolStripMenuItem->Text = L"Load Vector";
				 this->LoadVectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::LoadVectorToolStripMenuItem_Click);
				 // 
				 // tableLayoutPanel1
				 // 
				 this->tableLayoutPanel1->ColumnCount = 2;
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 1, 0);
				 this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 0, 0);
				 this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel1->Location = System::Drawing::Point(0, 27);
				 this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				 this->tableLayoutPanel1->RowCount = 1;
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
				 this->tableLayoutPanel1->Size = System::Drawing::Size(512, 425);
				 this->tableLayoutPanel1->TabIndex = 2;
				 // 
				 // flowLayoutPanel1
				 // 
				 this->flowLayoutPanel1->Controls->Add(this->InputLabel);
				 this->flowLayoutPanel1->Controls->Add(this->Input);
				 this->flowLayoutPanel1->Controls->Add(this->VectorLabel);
				 this->flowLayoutPanel1->Controls->Add(this->VectorList);
				 this->flowLayoutPanel1->Controls->Add(this->richTextBox1);
				 this->flowLayoutPanel1->Location = System::Drawing::Point(260, 4);
				 this->flowLayoutPanel1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
				 this->flowLayoutPanel1->Size = System::Drawing::Size(248, 415);
				 this->flowLayoutPanel1->TabIndex = 0;
				 // 
				 // InputLabel
				 // 
				 this->InputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->InputLabel->AutoSize = true;
				 this->InputLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
				 this->InputLabel->Location = System::Drawing::Point(4, 0);
				 this->InputLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->InputLabel->Name = L"InputLabel";
				 this->InputLabel->Size = System::Drawing::Size(48, 19);
				 this->InputLabel->TabIndex = 0;
				 this->InputLabel->Text = L"Input";
				 // 
				 // Input
				 // 
				 this->Input->Location = System::Drawing::Point(4, 23);
				 this->Input->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->Input->Multiline = true;
				 this->Input->Name = L"Input";
				 this->Input->Size = System::Drawing::Size(239, 196);
				 this->Input->TabIndex = 1;
				 this->Input->TextChanged += gcnew System::EventHandler(this, &WindowsForm::Input_TextChanged);
				 // 
				 // VectorLabel
				 // 
				 this->VectorLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->VectorLabel->AutoSize = true;
				 this->VectorLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
				 this->VectorLabel->Location = System::Drawing::Point(4, 223);
				 this->VectorLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->VectorLabel->Name = L"VectorLabel";
				 this->VectorLabel->Size = System::Drawing::Size(58, 19);
				 this->VectorLabel->TabIndex = 2;
				 this->VectorLabel->Text = L"Vector";
				 // 
				 // VectorList
				 // 
				 this->VectorList->FormattingEnabled = true;
				 this->VectorList->ItemHeight = 15;
				 this->VectorList->Location = System::Drawing::Point(4, 246);
				 this->VectorList->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->VectorList->Name = L"VectorList";
				 this->VectorList->Size = System::Drawing::Size(239, 154);
				 this->VectorList->TabIndex = 3;
				 // 
				 // flowLayoutPanel2
				 // 
				 this->flowLayoutPanel2->Controls->Add(this->OutputLabel);
				 this->flowLayoutPanel2->Controls->Add(this->Output);
				 this->flowLayoutPanel2->Location = System::Drawing::Point(4, 4);
				 this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
				 this->flowLayoutPanel2->Size = System::Drawing::Size(248, 415);
				 this->flowLayoutPanel2->TabIndex = 1;
				 // 
				 // OutputLabel
				 // 
				 this->OutputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
				 this->OutputLabel->AutoSize = true;
				 this->OutputLabel->Font = (gcnew System::Drawing::Font(L"�L�n������", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
					 System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
				 this->OutputLabel->Location = System::Drawing::Point(4, 0);
				 this->OutputLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->OutputLabel->Name = L"OutputLabel";
				 this->OutputLabel->Size = System::Drawing::Size(61, 19);
				 this->OutputLabel->TabIndex = 0;
				 this->OutputLabel->Text = L"Output";
				 // 
				 // Output
				 // 
				 this->Output->Font = (gcnew System::Drawing::Font(L"�s�ө���", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(136)));
				 this->Output->Location = System::Drawing::Point(4, 23);
				 this->Output->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->Output->Multiline = true;
				 this->Output->Name = L"Output";
				 this->Output->ReadOnly = true;
				 this->Output->Size = System::Drawing::Size(243, 390);
				 this->Output->TabIndex = 1;
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->FileName = L"openFileDialog1";
				 this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WindowsForm::openFileDialog1_FileOk);
				 // 
				 // richTextBox1
				 // 
				 this->richTextBox1->Location = System::Drawing::Point(3, 407);
				 this->richTextBox1->Name = L"richTextBox1";
				 this->richTextBox1->Size = System::Drawing::Size(8, 8);
				 this->richTextBox1->TabIndex = 4;
				 this->richTextBox1->Text = L"";
				 // 
				 // WindowsForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(512, 452);
				 this->Controls->Add(this->tableLayoutPanel1);
				 this->Controls->Add(this->menuStrip2);
				 this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->Name = L"WindowsForm";
				 this->Text = L"VectorExample";
				 this->Load += gcnew System::EventHandler(this, &WindowsForm::WindowsForm_Load);
				 this->menuStrip2->ResumeLayout(false);
				 this->menuStrip2->PerformLayout();
				 this->tableLayoutPanel1->ResumeLayout(false);
				 this->flowLayoutPanel1->ResumeLayout(false);
				 this->flowLayoutPanel1->PerformLayout();
				 this->flowLayoutPanel2->ResumeLayout(false);
				 this->flowLayoutPanel2->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private: System::Void WindowsForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void LoadVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//�}��Dialog
		openFileDialog1->ShowDialog();
	}
	private: System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
	{
		//��Input textbox������J���ܮɡA�K�|�i�J���禡
		//���o�V�q���
		std::vector<Vector> vectors = dataManager->GetVectors();
		//�P�_��J�ۤ���'\n'�A�è������r��-1��m
		if (Input->Text->Length - 1 >= 0 && Input->Text[Input->Text->Length - 1] == '\n')
		{
			//�N�ϥΪ̿�J�r��(�buserInput��)�A�̪ťէ@����
			array<String^> ^userCommand = userInput->Split(' ');
			//�r�����A�Y���O��"print"�����p
			if (userCommand[0] == "print")
			{
				//�w�N��X�Ȧs
				String^ outputTemp = "";
				//�z�Lfor�j��A�q�V�q��Ƥ���X�����ܼ�
				for (unsigned int i = 0; i < vectors.size(); i++)
				{
					//�Y�ܼƦW�ٻP���O�ܼƦW�ٲŦX
					if (userCommand[1] == gcnew String(vectors[i].Name.c_str()))
					{
						//�N��X�榡�s�J�Ȧs
						outputTemp += "[";
						//�N��X��Ʀs�J�Ȧs
						for (unsigned int j = 0; j < vectors[i].Data.size(); j++)
						{
							outputTemp += vectors[i].Data[j].ToString();
							if (j != vectors[i].Data.size() - 1)
								outputTemp += ",";
						}
						//�N��X�榡�s�J�Ȧs�A�åB����
						outputTemp += "]" + Environment::NewLine;
						//��X�Ȧs��T
						Output->Text += gcnew String(vectors[i].Name.c_str()) + " = " + outputTemp;
						break;
					}
				}
			}
			//�Ϥ��h�P�_�䤣����O
			else
			{
				Output->Text += "-Processor-" + Environment::NewLine;
				// �ϥ�Processor
				std::vector<std::string> prosIn;
				for (int i = 0; i < userCommand->Length; i++)
				{
					std::string str = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(userCommand[i])).ToPointer();
					prosIn.push_back(str);
				}
				std::string prosOut = Processor::Start(prosIn);
				String^ Str = gcnew String(prosOut.c_str());
				Output->Text += Str + Environment::NewLine;
			}
			userInput = "";
		}
		else
		{
			//�N�ϥΪ̿�J�r��(�bText box��)�A��'\n'�@����
			array<String^> ^userCommand = Input->Text->Split('\n');
			//�ñN�̫�@��A�@���ثe�ϥΪ̿�J���O
			userInput = userCommand[userCommand->Length - 1];
		}

	}
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		//�bDialog���UOK�K�|�i�J���禡
		//�r�����string^ to string
		std::string tempFileName;
		MarshalString(openFileDialog1->FileName, tempFileName);
		Output->Text += "-Check if Vectors file-" + Environment::NewLine;
		std::string name;
		for (char c : tempFileName)
		{
			if (c == '\\')
				name = "";
			else
			{
				name += c;
			}
		}
		if (name[0] == 'v' || name[0] == 'V') 
		{
			Processor::isVector = true;
			Output->Text += "TRUE" + Environment::NewLine;
		}
		else 
		{
			Processor::isVector = false;
			Output->Text += "FALSE" + Environment::NewLine;
		}
		//�N�ɮ׸��|�W�ٶǤJdataManager
		dataManager->SetFileName(tempFileName);
		//Ū�����
		if (dataManager->LoadVectorData(Processor::isVector))
		{
			// �ݩ�ŪVector�����p
			if (Processor::isVector)
			{
				//�NVectorList�����إ����M��
				VectorList->Items->Clear();
				//���o�Ҧ��V�q���
				std::vector<Vector> vectors = dataManager->GetVectors();
				Processor::SourceVectors.clear();
				Processor::SourceVectors = vectors;
				for (unsigned int i = 0; i < vectors.size(); i++)
				{
					//�N�ɮצW�٦s�J�Ȧs
					std::string tempString = vectors[i].Name;
					//�N��X�榡�s�J�Ȧs
					tempString += " [";
					//�N��X��Ʀs�J�Ȧs
					for (unsigned int j = 0; j < vectors[i].Data.size(); j++)
					{
						std::string scalarString = std::to_string(vectors[i].Data[j]);
						tempString += scalarString.substr(0, scalarString.size() - 5);
						if (j != vectors[i].Data.size() - 1)
							tempString += ",";
					}
					//�N��X�榡�s�J�Ȧs
					tempString += "]";
					//�N���إ[�JVectorList��
					VectorList->Items->Add(gcnew String(tempString.c_str()));
				}

				Output->Text += "-Vector datas have been loaded-" + Environment::NewLine;
			}
			else
			{
				// �ݩ�Matrix
				//�NVectorList�����إ����M��
				VectorList->Items->Clear();
				//���o�Ҧ��V�q���
				std::vector<Matrix> Mats = dataManager->GetMatrices();
				Processor::SourceMatrices.clear();
				Processor::SourceMatrices = Mats;
				for (unsigned int i = 0; i < Mats.size(); i++)
				{
					//�N�ɮצW�٦s�J�Ȧs
					std::string tempString;
					VectorList->Items->Add(gcnew String(Mats[i].Name.c_str()) + Environment::NewLine);
					//�N��X�榡�s�J�Ȧs
					tempString += " [";
					//�N��X��Ʀs�J�Ȧs
					for (unsigned int j = 0; j < Mats[i].Data.size(); j++)
					{
						for (unsigned int k = 0; k < Mats[i].Data[i].size(); k++)
						{
							std::string scalarString = std::to_string(Mats[i].Data[j][k]);
							tempString += scalarString.substr(0, scalarString.size() - 5);
							if (k != Mats[i].Data[j].size() - 1)
								tempString += ",";
						}
						VectorList->Items->Add(gcnew String(tempString.c_str()) + Environment::NewLine);
						tempString = "";
					}
					//�N��X�榡�s�J�Ȧs
					tempString += "]";
					VectorList->Items->Add(gcnew String(tempString.c_str()) + Environment::NewLine);
				}

				Output->Text += "-Matrices data have been loaded-" + Environment::NewLine;
			}
		}
	}
	};
}
