#pragma once
#include <vector>
#include <string>
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include "ShakerSort.h"
#include "Database.h"

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
	using namespace System::Runtime::InteropServices;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//инициализация данных
			currentArray = gcnew System::Collections::Generic::List<int>();
		lastOriginalArray = gcnew System::Collections::Generic::List<int>();
		lastOperationWasSort = false;
		currentUsername = "";

			//инициализация sqlite базы данных
			try {
				//создание объекта базы данных
				db = new ::Database("sorting.db");  //глобальное пространство имен

				if (db->open()) {
					db->createTables();
					lblStatus->Text = "База данных SQLite подключена. Готов к работе.";
					lblStatus->ForeColor = Color::Green;
				}
				else {
					lblStatus->Text = "Ошибка подключения к БД SQLite!";
					lblStatus->ForeColor = Color::Red;
				}
			}
			catch (Exception^ ex) {
				lblStatus->Text = "Ошибка инициализации БД: " + ex->Message;
				lblStatus->ForeColor = Color::Red;
			}
			catch (...) {
				lblStatus->Text = "Неизвестная ошибка инициализации БД!";
				lblStatus->ForeColor = Color::Red;
			}
		}

	protected:
		//освободить все используемые ресурсы
		~MainForm()
		{
			//закрываем базу данных
			if (db != nullptr) {
				db->close();
				delete db;
				db = nullptr;
			}

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
	private: System::Windows::Forms::Button^ btnHelp;
	
	private: System::Windows::Forms::Label^ labelPassword;
	private: System::Windows::Forms::Label^ labelArray;
	private: System::Windows::Forms::Label^ labelHistory;
	private: System::Windows::Forms::ListBox^ listHistory;
	private: System::Windows::Forms::Label^ lblStatus;

		   //данные программы
	private: System::Collections::Generic::List<int>^ currentArray;
	private: System::Collections::Generic::List<int>^ lastOriginalArray;
	private: bool lastOperationWasSort;
	private: System::String^ currentUsername;
	private: ::Database* db;  //указатель на нашу SQLite базу данных

	private:
		//обязательная переменная конструктора
		System::ComponentModel::Container^ components;

		//вспомогательная функция для преобразования String^ в std::string
	private:
		std::string ConvertToString(System::String^ s) {
			if (s == nullptr || s->Length == 0)
				return "";

			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string result = chars;
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
			return result;
		}

		//функция для преобразования std::string в String^
	private:
		String^ ConvertToManagedString(const std::string& s) {
			return gcnew String(s.c_str());
		}

		// вспомогательная функция: парсит txtArray в std::vector<int>
		std::vector<int> ParseTextToVector()
		{
			std::vector<int> out;
			array<String^>^ parts = txtArray->Text->Trim()->Split(' ');
			for each (String ^ part in parts) {
				if (part->Length > 0) {
					try { out.push_back(Convert::ToInt32(part)); }
					catch (Exception^) { }
				}
			}
			return out;
		}

		// вспомогательная функция: обновляет txtArray и currentArray из вектора
		void UpdateArrayDisplayAndCurrent(const std::vector<int>& vec)
		{
			txtArray->Clear();
			currentArray->Clear();
			for (int v : vec) { txtArray->AppendText(v.ToString() + " "); currentArray->Add(v); }
		}

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->groupAuth = (gcnew System::Windows::Forms::GroupBox());
			this->labelPassword = (gcnew System::Windows::Forms::Label());
			this->labelLogin = (gcnew System::Windows::Forms::Label());
			this->btnRegister = (gcnew System::Windows::Forms::Button());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->txtLogin = (gcnew System::Windows::Forms::TextBox());
			this->btnHelp = (gcnew System::Windows::Forms::Button());
			this->groupArray = (gcnew System::Windows::Forms::GroupBox());
			this->labelArray = (gcnew System::Windows::Forms::Label());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnSort = (gcnew System::Windows::Forms::Button());
			this->btnGenerate = (gcnew System::Windows::Forms::Button());
			this->txtArray = (gcnew System::Windows::Forms::RichTextBox());
			this->groupHistory = (gcnew System::Windows::Forms::GroupBox());
			this->listHistory = (gcnew System::Windows::Forms::ListBox());
			this->labelHistory = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
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
			this->groupAuth->Location = System::Drawing::Point(15, 15);
			this->groupAuth->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupAuth->Name = L"groupAuth";
			this->groupAuth->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupAuth->Size = System::Drawing::Size(990, 108);
			this->groupAuth->TabIndex = 0;
			this->groupAuth->TabStop = false;
			this->groupAuth->Text = L"Авторизация";
			// 
			// labelPassword
			// 
			this->labelPassword->AutoSize = true;
			this->labelPassword->Location = System::Drawing::Point(300, 38);
			this->labelPassword->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelPassword->Name = L"labelPassword";
			this->labelPassword->Size = System::Drawing::Size(71, 20);
			this->labelPassword->TabIndex = 5;
			this->labelPassword->Text = L"Пароль:";
			// 
			// labelLogin
			// 
			this->labelLogin->AutoSize = true;
			this->labelLogin->Location = System::Drawing::Point(22, 38);
			this->labelLogin->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelLogin->Name = L"labelLogin";
			this->labelLogin->Size = System::Drawing::Size(59, 20);
			this->labelLogin->TabIndex = 4;
			this->labelLogin->Text = L"Логин:";
			// 
			// btnRegister
			// 
			this->btnRegister->Location = System::Drawing::Point(735, 32);
			this->btnRegister->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnRegister->Name = L"btnRegister";
			this->btnRegister->Size = System::Drawing::Size(150, 38);
			this->btnRegister->TabIndex = 3;
			this->btnRegister->Text = L"Регистрация";
			this->btnRegister->UseVisualStyleBackColor = true;
			this->btnRegister->Click += gcnew System::EventHandler(this, &MainForm::btnRegister_Click);
			// 
			// btnLogin
			// 
			this->btnLogin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->btnLogin->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->btnLogin->Location = System::Drawing::Point(600, 32);
			this->btnLogin->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(120, 38);
			this->btnLogin->TabIndex = 2;
			this->btnLogin->Text = L"Войти";
			this->btnLogin->UseVisualStyleBackColor = false;
			this->btnLogin->Click += gcnew System::EventHandler(this, &MainForm::btnLogin_Click);
			// 
			// txtPassword
			// 
			this->txtPassword->Location = System::Drawing::Point(390, 34);
			this->txtPassword->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(178, 26);
			this->txtPassword->TabIndex = 1;
			this->txtPassword->Text = L"123";
			this->txtPassword->UseSystemPasswordChar = true;
			// 
			// txtLogin
			// 
			this->txtLogin->Location = System::Drawing::Point(105, 34);
			this->txtLogin->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->txtLogin->Name = L"txtLogin";
			this->txtLogin->Size = System::Drawing::Size(148, 26);
			this->txtLogin->TabIndex = 0;
			this->txtLogin->Text = L"user1";
			// 
			// btnHelp
			// 
			this->btnHelp->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(152)),
				static_cast<System::Int32>(static_cast<System::Byte>(219)));
			this->btnHelp->ForeColor = System::Drawing::Color::White;
			this->btnHelp->Location = System::Drawing::Point(800, 784);
			this->btnHelp->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnHelp->Name = L"btnHelp";
			this->btnHelp->Size = System::Drawing::Size(180, 38);
			this->btnHelp->TabIndex = 6;
			this->btnHelp->Text = L"Справка";
			this->btnHelp->UseVisualStyleBackColor = false;
			this->btnHelp->Click += gcnew System::EventHandler(this, &MainForm::btnHelp_Click);
			// 
			// groupArray
			// 
			this->groupArray->Controls->Add(this->labelArray);
			this->groupArray->Controls->Add(this->btnSave);
			this->groupArray->Controls->Add(this->btnSort);
			this->groupArray->Controls->Add(this->btnGenerate);
			this->groupArray->Controls->Add(this->txtArray);
			this->groupArray->Location = System::Drawing::Point(15, 138);
			this->groupArray->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupArray->Name = L"groupArray";
			this->groupArray->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupArray->Size = System::Drawing::Size(990, 277);
			this->groupArray->TabIndex = 1;
			this->groupArray->TabStop = false;
			this->groupArray->Text = L"Работа с массивом";
			// 
			// labelArray
			// 
			this->labelArray->AutoSize = true;
			this->labelArray->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelArray->Location = System::Drawing::Point(22, 38);
			this->labelArray->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelArray->Name = L"labelArray";
			this->labelArray->Size = System::Drawing::Size(229, 20);
			this->labelArray->TabIndex = 6;
			this->labelArray->Text = L"Массив (через пробел):";
			// 
			// btnSave
			// 
			this->btnSave->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(7)));
			this->btnSave->ForeColor = System::Drawing::Color::Black;
			this->btnSave->Location = System::Drawing::Point(412, 208);
			this->btnSave->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(180, 46);
			this->btnSave->TabIndex = 5;
			this->btnSave->Text = L"Сохранить в БД";
			this->btnSave->UseVisualStyleBackColor = false;
			this->btnSave->Click += gcnew System::EventHandler(this, &MainForm::btnSave_Click);
			// 
			// btnSort
			// 
			this->btnSort->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(111)), static_cast<System::Int32>(static_cast<System::Byte>(66)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)));
			this->btnSort->ForeColor = System::Drawing::Color::White;
			this->btnSort->Location = System::Drawing::Point(218, 208);
			this->btnSort->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnSort->Name = L"btnSort";
			this->btnSort->Size = System::Drawing::Size(180, 46);
			this->btnSort->TabIndex = 4;
			this->btnSort->Text = L"Сортировать";
			this->btnSort->UseVisualStyleBackColor = false;
			this->btnSort->Click += gcnew System::EventHandler(this, &MainForm::btnSort_Click);
			// 
			// btnGenerate
			// 
			this->btnGenerate->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(167)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btnGenerate->ForeColor = System::Drawing::Color::White;
			this->btnGenerate->Location = System::Drawing::Point(22, 208);
			this->btnGenerate->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->btnGenerate->Name = L"btnGenerate";
			this->btnGenerate->Size = System::Drawing::Size(180, 46);
			this->btnGenerate->TabIndex = 3;
			this->btnGenerate->Text = L"Сгенерировать";
			this->btnGenerate->UseVisualStyleBackColor = false;
			this->btnGenerate->Click += gcnew System::EventHandler(this, &MainForm::btnGenerate_Click);
			// 
			// txtArray
			// 
			this->txtArray->Location = System::Drawing::Point(22, 69);
			this->txtArray->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->txtArray->Name = L"txtArray";
			this->txtArray->Size = System::Drawing::Size(943, 121);
			this->txtArray->TabIndex = 2;
			this->txtArray->Text = L"5 3 8 1 2 9 4 7 6";
			// 
			// groupHistory
			// 
			this->groupHistory->Controls->Add(this->listHistory);
			this->groupHistory->Controls->Add(this->labelHistory);
			this->groupHistory->Location = System::Drawing::Point(15, 431);
			this->groupHistory->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupHistory->Name = L"groupHistory";
			this->groupHistory->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->groupHistory->Size = System::Drawing::Size(990, 308);
			this->groupHistory->TabIndex = 2;
			this->groupHistory->TabStop = false;
			this->groupHistory->Text = L"База данных - История (SQLite)";
			// 
			// listHistory
			// 
			this->listHistory->FormattingEnabled = true;
			this->listHistory->ItemHeight = 20;
			this->listHistory->Location = System::Drawing::Point(22, 62);
			this->listHistory->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->listHistory->Name = L"listHistory";
			this->listHistory->Size = System::Drawing::Size(943, 224);
			this->listHistory->TabIndex = 1;
			// 
			// labelHistory
			// 
			this->labelHistory->AutoSize = true;
			this->labelHistory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHistory->Location = System::Drawing::Point(22, 31);
			this->labelHistory->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelHistory->Name = L"labelHistory";
			this->labelHistory->Size = System::Drawing::Size(205, 20);
			this->labelHistory->TabIndex = 0;
			this->labelHistory->Text = L"История сохранений:";
			// 
			// lblStatus
			// 
			this->lblStatus->AutoSize = true;
			this->lblStatus->Location = System::Drawing::Point(22, 754);
			this->lblStatus->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(145, 20);
			this->lblStatus->TabIndex = 4;
			this->lblStatus->Text = L"Статусная строка";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1026, 844);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->groupHistory);
			this->Controls->Add(this->btnHelp);
			this->Controls->Add(this->groupArray);
			this->Controls->Add(this->groupAuth);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->MaximumSize = System::Drawing::Size(1048, 900);
			this->MinimumSize = System::Drawing::Size(1048, 900);
			this->Name = L"MainForm";
			this->Text = L"Сортировщик массивов с SQLite БД";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
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

		//обработчики ошибок

	private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ login = txtLogin->Text;
		String^ password = txtPassword->Text;

		if (login->Length == 0 || password->Length == 0) {
			MessageBox::Show("Введите логин и пароль!", "Ошибка входа",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (db == nullptr) {
			MessageBox::Show("База данных не инициализирована!", "Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		std::string username = ConvertToString(login);
		std::string pass = ConvertToString(password);

		int userId = db->getUserId(username);
		if (userId != -1) {
			// пользователь найден, проверяем пароль
			if (db->checkUser(username, pass)) {
				currentUsername = login;
				lblStatus->Text = "Вход выполнен: " + login + " (SQLite)";
				lblStatus->ForeColor = Color::Green;

				// блокируем поля авторизации
				this->txtLogin->Enabled = false;
				this->txtPassword->Enabled = false;
				this->btnLogin->Enabled = false;
				this->btnRegister->Enabled = false;

				LoadHistory();
			}
			else {
				MessageBox::Show("Неверный пароль.", "Ошибка входа",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else {
			// пользователь не найден, предлагаем зарегистрироваться
			if (MessageBox::Show("Пользователь не найден. Зарегистрироваться?", "Вход",
				MessageBoxButtons::YesNo, MessageBoxIcon::Question) == Windows::Forms::DialogResult::Yes) {
				if (db->addUser(username, pass)) {
					currentUsername = login;
					lblStatus->Text = "Зарегистрирован и вошел: " + login;
					lblStatus->ForeColor = Color::Green;
					this->txtLogin->Enabled = false;
					this->txtPassword->Enabled = false;
					this->btnLogin->Enabled = false;
					this->btnRegister->Enabled = false;
					LoadHistory();
				}
				else {
					MessageBox::Show("Ошибка регистрации! Попробуйте другой логин.", "Ошибка",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}
	}

	private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ login = txtLogin->Text;
		String^ password = txtPassword->Text;

		if (login->Length == 0 || password->Length == 0) {
			MessageBox::Show("Введите логин и пароль!", "Ошибка регистрации",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (db == nullptr) {
			MessageBox::Show("База данных не инициализирована!", "Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		std::string username = ConvertToString(login);
		std::string pass = ConvertToString(password);

		int userId = db->getUserId(username);
		if (userId != -1) {
			MessageBox::Show("Логин уже занят. Выберите другой логин или войдите.", "Ошибка регистрации",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		if (db->addUser(username, pass)) {
			MessageBox::Show("Пользователь '" + login + "' успешно зарегистрирован в SQLite БД!\n\n" +
				"Теперь вы можете войти в систему.",
				"Регистрация успешна",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			lblStatus->Text = "Зарегистрирован новый пользователь: " + login;
			lblStatus->ForeColor = Color::DarkOrange;
		}
		else {
			MessageBox::Show("Ошибка регистрации! Попробуйте другой логин.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}


	private: System::Void btnHelp_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ help = "Использование:\n";
		help += "1) Введите логин и пароль.\n";
		help += "2) Нажмите 'Войти' если у вас есть учетная запись.\n";
		help += "Если учетной записи нет, при попытке входа будет предложено зарегистрироваться.\n";
		help += "3) После входа вы сможете генерировать, сортировать и сохранять массивы в базу.\n";
		help += "4) Кнопка 'Сохранить в БД' сохраняет текущий массив для вошедшего пользователя.\n\n";
		

		MessageBox::Show(help, "Справка", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void btnGenerate_Click(System::Object^ sender, System::EventArgs^ e) {
		Random^ rand = gcnew Random();
		int count = rand->Next(5, 25);

		std::vector<int> vec;
		vec.reserve(count);
		for (int i = 0; i < count; ++i) vec.push_back(rand->Next(0, 100));

	
		UpdateArrayDisplayAndCurrent(vec);

	
		lastOriginalArray->Clear();
		lastOperationWasSort = false;

		lblStatus->Text = String::Format("Сгенерировано {0} случайных чисел (0-99)", count);
		lblStatus->ForeColor = Color::Blue;
	}

	private: System::Void btnSort_Click(System::Object^ sender, System::EventArgs^ e) {
		std::vector<int> parsed = ParseTextToVector();
		if (parsed.empty()) {
			MessageBox::Show("Введите массив чисел!\n\nПример: 5 3 8 1 2",
				"Ошибка сортировки",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		lastOriginalArray->Clear();
		for (int v : parsed) lastOriginalArray->Add(v);

		std::vector<int> sortedVec = parsed;
		ShakerSort::sort(sortedVec);

		
		UpdateArrayDisplayAndCurrent(sortedVec);
		lastOperationWasSort = true;

		lblStatus->Text = String::Format("Отсортировано {0} элементов (шейкерная сортировка)", parsed.size());
		lblStatus->ForeColor = Color::Purple;
	}

private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
	if (currentUsername == nullptr || currentUsername->Length == 0) {
		MessageBox::Show("Сначала войдите в систему!", "Ошибка сохранения",
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	if (db == nullptr) {
		MessageBox::Show("База данных не инициализирована!", "Ошибка",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

    std::vector<int> original, sorted;

    if (lastOperationWasSort && lastOriginalArray->Count > 0) {
        for each (int v in lastOriginalArray) original.push_back(v);
        for each (int v in currentArray) sorted.push_back(v);
    }
    else {
        original = ParseTextToVector();
        if (original.empty()) {
            MessageBox::Show("Нет данных для сохранения!\nСгенерируйте или введите массив.",
                "Ошибка сохранения",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
        sorted = original;
        ShakerSort::sort(sorted);
    }

	std::string username = ConvertToString(currentUsername);

	if (db->saveArray(username, original, sorted)) {
		//добавляем запись в историю на форме
		String^ historyItem = DateTime::Now.ToString("HH:mm:ss") +
			" - " + original.size() + " элементов (оригинальный: " +
			original[0] + "..." + original[original.size() - 1] + ")";
		listHistory->Items->Insert(0, historyItem);

		lblStatus->Text = "Массив успешно сохранен в SQLite БД";
		lblStatus->ForeColor = Color::Green;

		MessageBox::Show("Данные сохранены в SQLite базу данных!\n\n" +
			"Файл БД: sorting.db\n" +
			"Оригинальный массив: " + original.size() + " элементов\n" +
			"Отсортированный массив: " + sorted.size() + " элементов",
			"Сохранение успешно",
			MessageBoxButtons::OK, MessageBoxIcon::Information);

		//обновляем историю из БД
		LoadHistory();

			//обновляем currentArray оригинальными значениями
			currentArray->Clear();
			for (int num : original) {
				currentArray->Add(num);
			}

			// reset sort tracking
			lastOriginalArray->Clear();
			lastOperationWasSort = false;
	}
	else {
		MessageBox::Show("Ошибка сохранения в БД SQLite!", "Ошибка",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}



	private: void LoadHistory() {
		if (currentUsername == nullptr || currentUsername->Length == 0) return;
		if (db == nullptr) return;

		listHistory->Items->Clear();

		std::string username = ConvertToString(currentUsername);
		auto history = db->getUserArrays(username);

		if (history.empty()) {
			listHistory->Items->Add("История пуста (SQLite БД)");
			listHistory->Items->Add("Сохраните первый массив!");
			return;
		}

		//ограничиваем показ 20 последними записями
		int count = 0;
		for (const auto& entry : history) {
			if (count++ >= 20) break;
			listHistory->Items->Add(ConvertToManagedString(entry));
		}

		lblStatus->Text = String::Format("Загружено {0} записей из SQLite БД", history.size());
	}
	};
}