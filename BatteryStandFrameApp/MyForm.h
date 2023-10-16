#pragma once

//void sendMess();

#include <windows.h>
#include <iostream>
#include <string>

namespace BatteryStandFrameApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label1;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(82, 31);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(112, 42);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(82, 92);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(95, 20);
			this->checkBox1->TabIndex = 1;
			this->checkBox1->Text = L"checkBox1";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(115, 143);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(28, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Info";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		
		HANDLE hPipe;
		const char* pipeName = "\\\\.\\pipe\\MyNamedPipe"; // Уникальное имя канала

		hPipe = CreateFileA(
			pipeName,                    // Имя канала
			GENERIC_WRITE,               // Права доступа
			0,                           // Флаги и атрибуты
			NULL,                        // Структура защиты (NULL означает использование стандартной защиты)
			OPEN_EXISTING,               // Открываем существующий канал
			0,                           // Флаги асинхронного режима (0 для синхронного режима)
			NULL                         // Дескриптор шаблона файла (не используется)
		);

		if (hPipe == INVALID_HANDLE_VALUE) {
			std::cerr << "Failed to open pipe. Error code: " << GetLastError() << std::endl;
			//return 1;
		}

		std::string message = "Message from pipe!";
		DWORD bytesWritten;
		BOOL result = WriteFile(hPipe, message.c_str(), message.size(), &bytesWritten, NULL);

		if (!result) {
			std::cerr << "Failed to write to pipe. Error code: " << GetLastError() << std::endl;
		}
		else {
			std::cout << "Message sent: " << message << std::endl;
		}

		CloseHandle(hPipe);

	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
