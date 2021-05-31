#pragma once
#include <msclr/marshal_cppstd.h>
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

	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Wyczyść wszystkie używane zasoby.
		/// </summary>
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
	private: System::Windows::Forms::ProgressBar^ progressBar1;

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obsługi projektanta — nie należy modyfikować
		/// jej zawartości w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_to_compress = (gcnew System::Windows::Forms::Button());
			this->button_to_decompress = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->SuspendLayout();
			// 
			// button_to_compress
			// 
			this->button_to_compress->Location = System::Drawing::Point(12, 12);
			this->button_to_compress->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_to_compress->Name = L"button_to_compress";
			this->button_to_compress->Size = System::Drawing::Size(131, 60);
			this->button_to_compress->TabIndex = 1;
			this->button_to_compress->Text = L"Compress file";
			this->button_to_compress->UseVisualStyleBackColor = true;
			this->button_to_compress->Click += gcnew System::EventHandler(this, &MyForm::button_to_compress_Click);
			// 
			// button_to_decompress
			// 
			this->button_to_decompress->Location = System::Drawing::Point(12, 78);
			this->button_to_decompress->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button_to_decompress->Name = L"button_to_decompress";
			this->button_to_decompress->Size = System::Drawing::Size(131, 60);
			this->button_to_decompress->TabIndex = 2;
			this->button_to_decompress->Text = L"Decompress file";
			this->button_to_decompress->UseVisualStyleBackColor = true;
			this->button_to_decompress->Click += gcnew System::EventHandler(this, &MyForm::button_to_decompress_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(13, 144);
			this->progressBar1->MarqueeAnimationSpeed = 20;
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(556, 61);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar1->TabIndex = 3;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(581, 217);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button_to_decompress);
			this->Controls->Add(this->button_to_compress);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"CompressionTool";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_to_compress_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "txt files (*.txt)|*.txt";
		openFileDialog1->FilterIndex = 1;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			Node node;
			Tree tree;
			const char* directory;
			marshal_context^ context = gcnew marshal_context();
			directory = context->marshal_as<const char*>(openFileDialog1->FileName);
			tree.root = node.first_read_of_the_file(directory);
			node.sort_list(tree.root);
			node.make_tree(tree.root);
			tree.create_compressed_file(directory);
			tree.delete_tree(tree.root);

			SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;

			saveFileDialog1->InitialDirectory = "c:\\";
			saveFileDialog1->Filter = "huf files (*.huf)|*.huf";
			saveFileDialog1->FilterIndex = 1;
			saveFileDialog1->RestoreDirectory = true;

			if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				directory = context->marshal_as<const char*>(saveFileDialog1->FileName);
				int result = rename("compressed.huf", directory);
			}
			else
				remove("compressed.huf");

			delete context;
			delete saveFileDialog1;
		}

		delete openFileDialog1;
	}
	
	private: System::Void button_to_decompress_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenFileDialog^ openFileDialog2 = gcnew OpenFileDialog;

		openFileDialog2->InitialDirectory = "c:\\";
		openFileDialog2->Filter = "huf files (*.huf)|*.huf";
		openFileDialog2->FilterIndex = 1;
		openFileDialog2->RestoreDirectory = true;

		if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			Tree tree;
			const char* directory;
			marshal_context^ context = gcnew marshal_context();
			directory = context->marshal_as<const char*>(openFileDialog2->FileName);
			tree.decompress_file(directory);
			tree.delete_tree(tree.root);

			SaveFileDialog^ saveFileDialog2 = gcnew SaveFileDialog;

			saveFileDialog2->InitialDirectory = "c:\\";
			saveFileDialog2->Filter = "txt files (*.txt)|*.txt";
			saveFileDialog2->FilterIndex = 1;
			saveFileDialog2->RestoreDirectory = true;

			if (saveFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				directory = context->marshal_as<const char*>(saveFileDialog2->FileName);
				int result = rename("decompressed.txt", directory);
			}
			else
				remove("decompressed.txt");

			delete context;
			delete saveFileDialog2;
		}

		delete openFileDialog2;
	}
};
}