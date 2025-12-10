#pragma once

#include <vector>
#include <string>

// СНАЧАЛА стандартные заголовки
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

// ОСТАЛЬНЫЕ ваши заголовки
#include "ShakerSort.h"
#include "FileDatabase.h"

using namespace msclr::interop;

namespace rps33 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::InteropServices;  // Для StringToHGlobalAnsi

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			// Инициализация данных
			currentArray = gcnew System::Collections::Generic::List<int>();
			currentUsername = "";
			lblStatus->Text = "Готов к работе. Войдите в систему.";
			lblStatus->ForeColor = Color::DarkBlue;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupAuth;
	private: System::Windows::Forms::GroupBox^ groupArray;
	private: System::Windows::Forms::GroupBox^ groupHistory;
	private: System::Windows::Forms::TextBox^ txtPassword;
	private: System::Windows::Forms::TextBox^ txtLogin;
	private: System::Windows::Forms::RichTextBox^ txtArray;
	private: System::Windows::Forms::Button^ btnRegister;
	private: System::Windows::Forms::Button^ btnLogin;
	private: System::Windows::Forms::Button^ btnSave;
	private: System::Windows::Forms::Button^ btnSort;
	private: System::Windows::Forms::Button^ btnGenerate;
	private: System::Windows::Forms::Label^ labelLogin;
	private: System::Windows::Forms::Button^ btnTest;
	private: System::Windows::Forms::Label^ labelPassword;
	private: System::Windows::Forms::Label^ labelArray;
	private: System::Windows::Forms::Label^ labelHistory;
	private: System::Windows::Forms::ListBox^ listHistory;
	private: System::Windows::Forms::Label^ lblStatus;

		   // Данные программы
	private: System::Collections::Generic::List<int>^ currentArray;
	private: System::String^ currentUsername;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

		// Вспомогательная функция для преобразования String^ в std::string
	private:
		std::string ConvertToString(System::String^ s) {
			if (s == nullptr || s->Length == 0)
				return "";

			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string result = chars;
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
			return result;
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupAuth = (gcnew System::Windows::Forms::GroupBox());
			this->groupArray = (gcnew System::Windows::Forms::GroupBox());
			this->groupHistory = (gcnew System::Windows::Forms::GroupBox());
			this->txtLogin = (gcnew System::Windows::Forms::TextBox());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->txtArray = (gcnew System::Windows::Forms::RichTextBox());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->btnRegister = (gcnew System::Windows::Forms::Button());
			this->btnGenerate = (gcnew System::Windows::Forms::Button());
			this->btnSort = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnTest = (gcnew System::Windows::Forms::Button());
			this->labelLogin = (gcnew System::Windows::Forms::Label());
			this->labelPassword = (gcnew System::Windows::Forms::Label());
			this->labelArray = (gcnew System::Windows::Forms::Label());
			this->labelHistory = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->listHistory = (gcnew System::Windows::Forms::ListBox());
			this->groupAuth->SuspendLayout();
			this->groupArray->SuspendLayout();
			this->groupHistory->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupAuth
			// 
			this->groupAuth->Controls->Add(this->labelPassword);
			this->groupAuth->Controls->Add(this->labelLogin);
			this->groupAuth->Controls->Add(this->btnRegister);
			this->groupAuth->Controls->Add(this->btnLogin);
			this->groupAuth->Controls->Add(this->txtPassword);
			this->groupAuth->Controls->Add(this->txtLogin);
			this->groupAuth->Location = System::Drawing::Point(10, 10);
			this->groupAuth->Name = L"groupAuth";
			this->groupAuth->Size = System::Drawing::Size(660, 70);
			this->groupAuth->TabIndex = 0;
			this->groupAuth->TabStop = false;
			this->groupAuth->Text = L"Авторизация";
			// 
			// groupArray
			// 
			this->groupArray->Controls->Add(this->labelArray);
			this->groupArray->Controls->Add(this->btnSave);
			this->groupArray->Controls->Add(this->btnSort);
			this->groupArray->Controls->Add(this->btnGenerate);
			this->groupArray->Controls->Add(this->txtArray);
			this->groupArray->Location = System::Drawing::Point(10, 90);
			this->groupArray->Name = L"groupArray";
			this->groupArray->Size = System::Drawing::Size(660, 180);
			this->groupArray->TabIndex = 1;
			this->groupArray->TabStop = false;
			this->groupArray->Text = L"Работа с массивом";
			// 
			// groupHistory
			// 
			this->groupHistory->Controls->Add(this->listHistory);
			this->groupHistory->Controls->Add(this->labelHistory);
			this->groupHistory->Location = System::Drawing::Point(10, 280);
			this->groupHistory->Name = L"groupHistory";
			this->groupHistory->Size = System::Drawing::Size(660, 200);
			this->groupHistory->TabIndex = 2;
			this->groupHistory->TabStop = false;
			this->groupHistory->Text = L"Базы данных - история";
			// 
			// txtLogin
			// 
			this->txtLogin->Location = System::Drawing::Point(70, 22);
			this->txtLogin->Name = L"txtLogin";
			this->txtLogin->Size = System::Drawing::Size(100, 20);
			this->txtLogin->TabIndex = 0;
			this->txtLogin->Text = L"user1";
			// 
			// txtPassword
			// 
			this->txtPassword->Location = System::Drawing::Point(260, 22);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(120, 20);
			this->txtPassword->TabIndex = 1;
			this->txtPassword->Text = L"123";
			this->txtPassword->UseSystemPasswordChar = true;
			// 
			// txtArray
			// 
			this->txtArray->Location = System::Drawing::Point(15, 45);
			this->txtArray->Name = L"txtArray";
			this->txtArray->Size = System::Drawing::Size(630, 80);
			this->txtArray->TabIndex = 2;
			this->txtArray->Text = L"5 3 8 1 2 9 4 7 6";
			// 
			// btnLogin
			// 
			this->btnLogin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnLogin->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btnLogin->Location = System::Drawing::Point(400, 21);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(80, 25);
			this->btnLogin->TabIndex = 2;
			this->btnLogin->Text = L"Войти";
			this->btnLogin->UseVisualStyleBackColor = false;
			this->btnLogin->Click += gcnew System::EventHandler(this, &MainForm::btnLogin_Click);
			// 
			// btnRegister
			// 
			this->btnRegister->Location = System::Drawing::Point(490, 21);
			this->btnRegister->Name = L"btnRegister";
			this->btnRegister->Size = System::Drawing::Size(100, 25);
			this->btnRegister->TabIndex = 3;
			this->btnRegister->Text = L"Регистрация";
			this->btnRegister->UseVisualStyleBackColor = true;
			this->btnRegister->Click += gcnew System::EventHandler(this, &MainForm::btnRegister_Click);
			// 
			// btnGenerate
			// 
			this->btnGenerate->Location = System::Drawing::Point(15, 135);
			this->btnGenerate->Name = L"btnGenerate";
			this->btnGenerate->Size = System::Drawing::Size(120, 30);
			this->btnGenerate->TabIndex = 3;
			this->btnGenerate->Text = L"Сгенерировать";
			this->btnGenerate->UseVisualStyleBackColor = true;
			this->btnGenerate->Click += gcnew System::EventHandler(this, &MainForm::btnGenerate_Click);
			// 
			// btnSort
			// 
			this->btnSort->Location = System::Drawing::Point(145, 135);
			this->btnSort->Name = L"btnSort";
			this->btnSort->Size = System::Drawing::Size(120, 30);
			this->btnSort->TabIndex = 4;
			this->btnSort->Text = L"Сортировать";
			this->btnSort->UseVisualStyleBackColor = true;
			this->btnSort->Click += gcnew System::EventHandler(this, &MainForm::btnSort_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(275, 135);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(120, 30);
			this->btnSave->TabIndex = 5;
			this->btnSave->Text = L"Сохранить в БД";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
			// 
			// btnTest
			// 
			this->btnTest->Location = System::Drawing::Point(540, 485);
			this->btnTest->Name = L"btnTest";
			this->btnTest->Size = System::Drawing::Size(100, 30);
			this->btnTest->TabIndex = 3;
			this->btnTest->Text = L"Тесты БД";
			this->btnTest->UseVisualStyleBackColor = true;
			this->btnTest->Click += gcnew System::EventHandler(this, &MainForm::btnTest_Click);
			// 
			// labelLogin
			// 
			this->labelLogin->AutoSize = true;
			this->labelLogin->Location = System::Drawing::Point(15, 25);
			this->labelLogin->Name = L"labelLogin";
			this->labelLogin->Size = System::Drawing::Size(41, 13);
			this->labelLogin->TabIndex = 4;
			this->labelLogin->Text = L"Логин:";
			// 
			// labelPassword
			// 
			this->labelPassword->AutoSize = true;
			this->labelPassword->Location = System::Drawing::Point(200, 25);
			this->labelPassword->Name = L"labelPassword";
			this->labelPassword->Size = System::Drawing::Size(48, 13);
			this->labelPassword->TabIndex = 5;
			this->labelPassword->Text = L"Пароль:";
			// 
			// labelArray
			// 
			this->labelArray->AutoSize = true;
			this->labelArray->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelArray->Location = System::Drawing::Point(15, 25);
			this->labelArray->Name = L"labelArray";
			this->labelArray->Size = System::Drawing::Size(148, 13);
			this->labelArray->TabIndex = 6;
			this->labelArray->Text = L"Массив (через пробел):";
			// 
			// labelHistory
			// 
			this->labelHistory->AutoSize = true;
			this->labelHistory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHistory->Location = System::Drawing::Point(15, 20);
			this->labelHistory->Name = L"labelHistory";
			this->labelHistory->Size = System::Drawing::Size(134, 13);
			this->labelHistory->TabIndex = 0;
			this->labelHistory->Text = L"История сохранений:";
			// 
			// lblStatus
			// 
			this->lblStatus->AutoSize = true;
			this->lblStatus->Location = System::Drawing::Point(15, 490);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(97, 13);
			this->lblStatus->TabIndex = 4;
			this->lblStatus->Text = L"Статусная строка";
			// 
			// listHistory
			// 
			this->listHistory->FormattingEnabled = true;
			this->listHistory->Location = System::Drawing::Point(15, 40);
			this->listHistory->Name = L"listHistory";
			this->listHistory->Size = System::Drawing::Size(630, 147);
			this->listHistory->TabIndex = 1;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(684, 561);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->btnTest);
			this->Controls->Add(this->groupHistory);
			this->Controls->Add(this->groupArray);
			this->Controls->Add(this->groupAuth);
			this->Name = L"MainForm";
			this->Text = L"Сортировщик массивов с БД";
			this->groupAuth->ResumeLayout(false);
			this->groupAuth->PerformLayout();
			this->groupArray->ResumeLayout(false);
			this->groupArray->PerformLayout();
			this->groupHistory->ResumeLayout(false);
			this->groupHistory->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// ========== ОБРАБОТЧИКИ СОБЫТИЙ ==========

	private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ login = txtLogin->Text;
		String^ password = txtPassword->Text;

		if (login->Length == 0 || password->Length == 0) {
			MessageBox::Show("Введите логин и пароль!", "Ошибка входа",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		currentUsername = login;
		lblStatus->Text = "Вход выполнен: " + login;
		lblStatus->ForeColor = Color::Green;

		// Загружаем историю
		LoadHistory();
	}

	private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ login = txtLogin->Text;
		String^ password = txtPassword->Text;

		if (login->Length == 0 || password->Length == 0) {
			MessageBox::Show("Введите логин и пароль!", "Ошибка регистрации",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		MessageBox::Show("Пользователь '" + login + "' успешно зарегистрирован!\n\n" +
			"Теперь вы можете войти в систему.",
			"Регистрация успешна",
			MessageBoxButtons::OK, MessageBoxIcon::Information);

		lblStatus->Text = "Зарегистрирован новый пользователь: " + login;
		lblStatus->ForeColor = Color::DarkOrange;
	}

	private: System::Void btnGenerate_Click(System::Object^ sender, System::EventArgs^ e) {
		Random^ rand = gcnew Random();
		int count = rand->Next(5, 25);

		txtArray->Clear();
		currentArray->Clear();

		for (int i = 0; i < count; i++) {
			int num = rand->Next(0, 100);
			currentArray->Add(num);
			txtArray->AppendText(num.ToString() + " ");
		}

		lblStatus->Text = String::Format("Сгенерировано {0} случайных чисел (0-99)", count);
		lblStatus->ForeColor = Color::Blue;
	}

	private: System::Void btnSort_Click(System::Object^ sender, System::EventArgs^ e) {
		array<String^>^ parts = txtArray->Text->Trim()->Split(' ');
		std::vector<int> stdArray;

		for each (String ^ part in parts) {
			if (part->Length > 0) {
				try {
					stdArray.push_back(Convert::ToInt32(part));
				}
				catch (Exception^) {}
			}
		}

		if (stdArray.empty()) {
			MessageBox::Show("Введите массив чисел!\n\nПример: 5 3 8 1 2",
				"Ошибка сортировки",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		ShakerSort::sort(stdArray);

		txtArray->Clear();
		for (int num : stdArray) {
			txtArray->AppendText(num.ToString() + " ");
		}

		currentArray->Clear();
		for (int num : stdArray) {
			currentArray->Add(num);
		}

		lblStatus->Text = String::Format("Отсортировано {0} элементов (шейкерная сортировка)", stdArray.size());
		lblStatus->ForeColor = Color::Purple;
	}

	private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentUsername == nullptr || currentUsername->Length == 0) {
			MessageBox::Show("Сначала войдите в систему!", "Ошибка сохранения",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (currentArray->Count == 0) {
			MessageBox::Show("Нет данных для сохранения!\nСгенерируйте или введите массив.",
				"Ошибка сохранения",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		std::vector<int> original, sorted;
		for each (int num in currentArray) {
			original.push_back(num);
			sorted.push_back(num);
		}

		ShakerSort::sort(sorted);

		// ИСПРАВЛЕННЫЙ ВЫЗОВ - используем ConvertToString вместо marshal_as
		std::string username = ConvertToString(currentUsername);

		if (FileDatabase::saveArray(username, original, sorted)) {
			String^ historyItem = DateTime::Now.ToString("HH:mm:ss") +
				" - " + original.size() + " элементов";
			listHistory->Items->Insert(0, historyItem);

			lblStatus->Text = "Массив успешно сохранен в БД";
			lblStatus->ForeColor = Color::Green;

			MessageBox::Show("Данные сохранены в базу данных!\n\n" +
				"Файл: " + currentUsername + "_arrays.txt",
				"Сохранение успешно",
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else {
			MessageBox::Show("Ошибка сохранения в БД!", "Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnTest_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ results = "ТЕСТЫ ПРОИЗВОДИТЕЛЬНОСТИ БАЗЫ ДАННЫХ\n\n";

		results += "1. Добавление 100 массивов в БД...\n";
		double time1 = FileDatabase::testAddArrays(100);
		results += String::Format("   Время: {0:F3} секунд\n\n", time1);

		results += "2. Загрузка массивов из БД...\n";
		double time2 = FileDatabase::testLoadArrays("test_user");
		results += String::Format("   Время: {0:F3} секунд\n\n", time2);

		results += "3. Очистка тестовой БД...\n";
		bool cleared = FileDatabase::clearUserHistory("test_user");
		results += String::Format("   Результат: {0}\n\n",
			cleared ? "УСПЕШНО" : "ОШИБКА");

		results += "Файлы БД создаются в папке с программой.\n";
		results += "Формат: username_arrays.txt";

		MessageBox::Show(results, "Результаты тестов БД",
			MessageBoxButtons::OK, MessageBoxIcon::Information);

		lblStatus->Text = "Тесты БД выполнены (см. результаты)";
		lblStatus->ForeColor = Color::DarkCyan;
	}






	private: void LoadHistory() {
		if (currentUsername == nullptr || currentUsername->Length == 0) return;

		listHistory->Items->Clear();

		// ИСПРАВЛЕННЫЙ ВЫЗОВ - используем ConvertToString вместо marshal_as
		std::string username = ConvertToString(currentUsername);
		auto history = FileDatabase::loadUserArrays(username);

		if (history.empty()) {
			listHistory->Items->Add("История пуста");
			listHistory->Items->Add("Сохраните первый массив!");
			return;
		}

		int count = 0;
		for (const auto& entry : history) {
			if (count++ >= 20) break;
			listHistory->Items->Add(gcnew String(entry.c_str()));
		}

		lblStatus->Text = String::Format("Загружено {0} записей из БД", history.size());
	}
	};
}