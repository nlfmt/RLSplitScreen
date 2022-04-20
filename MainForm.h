#pragma once

#include <string>

namespace RLSplitScreen {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;

	protected:

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Button^ btn_disable;
	private: System::Windows::Forms::Button^ btn_enable;
	private: System::Windows::Forms::TextBox^ logs;
	private: System::Windows::Forms::Panel^ titlebar;

	private: System::Windows::Forms::Button^ button1;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->btn_disable = (gcnew System::Windows::Forms::Button());
			this->btn_enable = (gcnew System::Windows::Forms::Button());
			this->logs = (gcnew System::Windows::Forms::TextBox());
			this->titlebar = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->titlebar->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label1->ForeColor = System::Drawing::Color::Gainsboro;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(138, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Rocket League SplitScreen";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->btn_disable, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->btn_enable, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(16, 305);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(271, 36);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// btn_disable
			// 
			this->btn_disable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btn_disable->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->btn_disable->FlatAppearance->BorderSize = 0;
			this->btn_disable->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btn_disable->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(220)),
				static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->btn_disable->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_disable->ForeColor = System::Drawing::Color::Gainsboro;
			this->btn_disable->Location = System::Drawing::Point(0, 0);
			this->btn_disable->Margin = System::Windows::Forms::Padding(0, 0, 5, 0);
			this->btn_disable->Name = L"btn_disable";
			this->btn_disable->Size = System::Drawing::Size(130, 36);
			this->btn_disable->TabIndex = 0;
			this->btn_disable->Text = L"Disable";
			this->btn_disable->UseVisualStyleBackColor = false;
			this->btn_disable->Click += gcnew System::EventHandler(this, &MainForm::btn_disable_Click);
			// 
			// btn_enable
			// 
			this->btn_enable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->btn_enable->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->btn_enable->FlatAppearance->BorderSize = 0;
			this->btn_enable->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(80)), static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btn_enable->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(120)), static_cast<System::Int32>(static_cast<System::Byte>(80)));
			this->btn_enable->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_enable->ForeColor = System::Drawing::Color::Gainsboro;
			this->btn_enable->Location = System::Drawing::Point(140, 0);
			this->btn_enable->Margin = System::Windows::Forms::Padding(5, 0, 0, 0);
			this->btn_enable->Name = L"btn_enable";
			this->btn_enable->Size = System::Drawing::Size(131, 36);
			this->btn_enable->TabIndex = 1;
			this->btn_enable->Text = L"Enable";
			this->btn_enable->UseVisualStyleBackColor = false;
			this->btn_enable->Click += gcnew System::EventHandler(this, &MainForm::btn_enable_Click);
			// 
			// logs
			// 
			this->logs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->logs->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(32)), static_cast<System::Int32>(static_cast<System::Byte>(32)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->logs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->logs->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->logs->ForeColor = System::Drawing::Color::Gainsboro;
			this->logs->Location = System::Drawing::Point(16, 42);
			this->logs->Multiline = true;
			this->logs->Name = L"logs";
			this->logs->ReadOnly = true;
			this->logs->Size = System::Drawing::Size(271, 257);
			this->logs->TabIndex = 0;
			this->logs->TabStop = false;
			this->logs->Text = resources->GetString(L"logs.Text");
			// 
			// titlebar
			// 
			this->titlebar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(96)), static_cast<System::Int32>(static_cast<System::Byte>(96)),
				static_cast<System::Int32>(static_cast<System::Byte>(96)));
			this->titlebar->Controls->Add(this->button1);
			this->titlebar->Controls->Add(this->label1);
			this->titlebar->Dock = System::Windows::Forms::DockStyle::Top;
			this->titlebar->Location = System::Drawing::Point(0, 0);
			this->titlebar->Margin = System::Windows::Forms::Padding(0);
			this->titlebar->Name = L"titlebar";
			this->titlebar->Size = System::Drawing::Size(299, 30);
			this->titlebar->TabIndex = 3;
			this->titlebar->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TitleBar_MouseDown);
			this->titlebar->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TitleBar_MouseMove);
			this->titlebar->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TitleBar_MouseUp);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->ForeColor = System::Drawing::Color::Gainsboro;
			this->button1->Location = System::Drawing::Point(221, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Close";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->ClientSize = System::Drawing::Size(299, 350);
			this->Controls->Add(this->titlebar);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->logs);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MinimumSize = System::Drawing::Size(250, 250);
			this->Name = L"MainForm";
			this->Text = L"RLSplitScreen";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->titlebar->ResumeLayout(false);
			this->titlebar->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		bool dragging;
		Point offset;

	private: System::Void btn_disable_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btn_enable_Click(System::Object^ sender, System::EventArgs^ e);

	public: void log(const char* msg);
	public: void log(std::string msg);

	private: System::Void TitleBar_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void TitleBar_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void TitleBar_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
};
}