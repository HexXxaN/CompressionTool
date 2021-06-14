#pragma once
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include "tree.h"

using namespace msclr::interop;

namespace CompressionTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Button^ button_to_compress;
	private: System::Windows::Forms::Button^ button_to_decompress;
	private: System::Windows::Forms::ProgressBar^ progressBar;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker2;
	private: System::Windows::Forms::Label^ label1;
	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->button_to_compress = (gcnew System::Windows::Forms::Button());
			this->button_to_decompress = (gcnew System::Windows::Forms::Button());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			
			this->SuspendLayout();
			
			this->button_to_compress->Location = System::Drawing::Point(12, 12);
			this->button_to_compress->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_to_compress->Name = L"button_to_compress";
			this->button_to_compress->Size = System::Drawing::Size(131, 60);
			this->button_to_compress->TabIndex = 1;
			this->button_to_compress->Text = L"Compress file";
			this->button_to_compress->UseVisualStyleBackColor = true;
			this->button_to_compress->Click += gcnew System::EventHandler(this, &MyForm::button_to_compress_Click);
			
			this->button_to_decompress->Location = System::Drawing::Point(12, 78);
			this->button_to_decompress->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_to_decompress->Name = L"button_to_decompress";
			this->button_to_decompress->Size = System::Drawing::Size(131, 60);
			this->button_to_decompress->TabIndex = 2;
			this->button_to_decompress->Text = L"Decompress file";
			this->button_to_decompress->UseVisualStyleBackColor = true;
			this->button_to_decompress->Click += gcnew System::EventHandler(this, &MyForm::button_to_decompress_Click);
			
			this->progressBar->Location = System::Drawing::Point(13, 144);
			this->progressBar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->progressBar->MarqueeAnimationSpeed = 20;
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(557, 62);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar->TabIndex = 3;
			
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker1_RunWorkerCompleted);
			
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker2_DoWork);
			this->backgroundWorker2->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::backgroundWorker2_RunWorkerCompleted);
			
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(197, 65);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(303, 32);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Compression ratio: --%";
			
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(581, 218);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar);
			this->Controls->Add(this->button_to_decompress);
			this->Controls->Add(this->button_to_compress);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->Text = L"CompressionTool";
			this->Activated += gcnew System::EventHandler(this, &MyForm::MyForm_Activated);
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void button_to_compress_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "txt files (*.txt)|*.txt";
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			this->button_to_decompress->Enabled = false;
			this->button_to_compress->Enabled = false;
			this->label1->Text = "Compression ratio: --%";
			this->backgroundWorker1->RunWorkerAsync(openFileDialog1->FileName);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
		}

		delete openFileDialog1;
	}

	private: System::Void button_to_decompress_Click(System::Object^ sender, System::EventArgs^ e)
	{	
		OpenFileDialog^ openFileDialog2 = gcnew OpenFileDialog;

		openFileDialog2->InitialDirectory = "c:\\";
		openFileDialog2->Filter = "huf files (*.huf)|*.huf";
		openFileDialog2->RestoreDirectory = true;

		if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			this->button_to_compress->Enabled = false;
			this->button_to_decompress->Enabled = false;
			this->label1->Text = "Compression ratio: --%";
			this->backgroundWorker2->RunWorkerAsync(openFileDialog2->FileName);
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
		}

		delete openFileDialog2;
	}
	
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
	{
		System::String^ dir = (System::String^)e->Argument;
		
		Node node;
		Tree tree;
		const char* directory;
		marshal_context^ context = gcnew marshal_context();
		directory = context->marshal_as<const char*>(dir);
		tree.root = node.first_read_of_the_file(directory);
		node.sort_list(tree.root);
		node.make_tree(tree.root);
		tree.create_compressed_file(directory);
		tree.delete_tree(tree.root);

		std::ifstream fileToCompress(directory, std::ios::binary);
		std::ifstream compressedFile("c:\\CompressionToolFolder\\compressed.huf", std::ios::binary);
		fileToCompress.seekg(0, std::ios::end);
		uint64_t fileToCompressSize = fileToCompress.tellg();
		compressedFile.seekg(0, std::ios::end);
		uint64_t compressedFileSize = compressedFile.tellg();
		fileToCompress.close();
		compressedFile.close();

		double ratio = (double) compressedFileSize/fileToCompressSize;
		ratio = std::ceil(ratio * 10000)/100;
		e->Result = ratio;
		
		delete context;
	}

	private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
	{
		this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
		this->label1->Text = "Compression ratio: " + e->Result->ToString() + "%";

		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;

		saveFileDialog1->InitialDirectory = "c:\\";
		saveFileDialog1->Filter = "huf files (*.huf)|*.huf";
		saveFileDialog1->RestoreDirectory = true;

		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{		
			marshal_context^ context = gcnew marshal_context();
			const char* directory = context->marshal_as<const char*>(saveFileDialog1->FileName);
			int result = rename("c:\\CompressionToolFolder\\compressed.huf", directory);
			
			delete context;
		}
		else
			remove("c:\\CompressionToolFolder\\compressed.huf");

		delete saveFileDialog1;

		this->button_to_decompress->Enabled = true;
		this->button_to_compress->Enabled = true;
	}

	private: System::Void backgroundWorker2_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
	{
		System::String^ dir = (System::String^)e->Argument;
		
		Tree tree;
		const char* directory;
		marshal_context^ context = gcnew marshal_context();
		directory = context->marshal_as<const char*>(dir);
		tree.decompress_file(directory);
		tree.delete_tree(tree.root);

		delete context;
	}

	private: System::Void backgroundWorker2_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e)
	{
		this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;

		SaveFileDialog^ saveFileDialog2 = gcnew SaveFileDialog;

		saveFileDialog2->InitialDirectory = "c:\\";
		saveFileDialog2->Filter = "txt files (*.txt)|*.txt";
		saveFileDialog2->RestoreDirectory = true;

		if (saveFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			marshal_context^ context = gcnew marshal_context();
			const char *directory = context->marshal_as<const char*>(saveFileDialog2->FileName);
			int result = rename("c:\\CompressionToolFolder\\decompressed.txt", directory);
			
			delete context;
		}
		else
			remove("c:\\CompressionToolFolder\\decompressed.txt");

		delete saveFileDialog2;
		
		this->button_to_decompress->Enabled = true;
		this->button_to_compress->Enabled = true;
	}
	
private: System::Void MyForm_Activated(System::Object^ sender, System::EventArgs^ e)
	{
	if (!Directory::Exists("c:\\CompressionToolFolder"))
		DirectoryInfo^ di = Directory::CreateDirectory("c:\\CompressionToolFolder");
	}
};
}
