#include <iostream>
#include <string>
#include <vector>
#define NOMINMAX
#include <Windows.h>

struct Recipe {
	std::string name;
	std::vector<std::string> ingredients;
	std::vector<int> amount;

	Recipe(std::string name, std::vector<std::string> ingredients, std::vector<int> amount)
		: name(name), ingredients(ingredients), amount(amount) {
	}

	Recipe addIngredient(Recipe& recipe, std::string newIngredient, int amountOfIngredient, int portions) {
		recipe.ingredients.push_back(newIngredient);
		recipe.amount.push_back(amountOfIngredient);
		return { recipe.name, recipe.ingredients, recipe.amount };
	}

	void printIngredients(int portions) const {
		for (int i = 0; i < ingredients.size() && i < amount.size(); i++) {
			std::cout << "- " << ingredients[i] << ": " << amount[i] * portions << std::endl;
		}
		std::cout << std::endl;
	}

	void removeIngredient(Recipe& recipe, std::string ingredientToDelete, int index) {
		for (int i = 0; i < recipe.ingredients.size(); i++) {
			if (recipe.ingredients[i] == ingredientToDelete) {
				index = i;
			}
		}

		if (index == -1) {
			std::cerr << "��������� ������ �����䳺��.\n\n";
			return;
		}

		recipe.ingredients.erase(recipe.ingredients.begin() + index);
	}

	void editIngredient(Recipe& recipe, std::string ingredientToEdit, int newAmountOfIngredients, bool* changed) {
		for (int i = 0; i < recipe.ingredients.size(); i++) {
			if (recipe.ingredients[i] == ingredientToEdit) {
				recipe.amount[i] = newAmountOfIngredients;
				*changed = true;
			}
		}

		if (!changed) {
			std::cout << "������� ���������� ����� �����䳺���. ��������� �� ���.\n\n";
			return;
		}

		*changed = false;
	}
};

template <typename T>
void getDataFromUser(T& variable, std::string text);
bool isCorrectInput();

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Recipe rec1{ "ϳ��", {"�������", "���", "�������"}, {150, 100, 1} };
	Recipe rec2{ "�����", {"����", "�������", "�����"}, {3, 2, 2} };
	Recipe rec3{ "�����", {"�����", "�������", "�������"}, {3, 1, 2} };

	short userInput;
	short portions;

	do {
		B:
		getDataFromUser(userInput, "\n������ ������:\n1. " + rec1.name + "\n2. " + rec2.name + "\n3. " + rec3.name + "\n> ");

		if (userInput < 1 || userInput > 3) {
			std::cout << "������� ����� �� ������� �������� ��������� ������. �������� ������.\n";
			goto B;
		}

		getDataFromUser(portions, "\n������ ������� ������: ");

		std::cout << "\n�����䳺��� �� " << portions << (portions == 1 ? " ������:" : portions > 1 && portions < 5
			? " ������:" : " ������:") << std::endl;
		switch (userInput) {
		case 1:
			rec1.printIngredients(portions);
			break;

		case 2:
			rec2.printIngredients(portions);
			break;

		case 3:
			rec3.printIngredients(portions);
			break;			
		}

		char character;

		do {
		M:
			getDataFromUser(character, "������ ������ �����䳺���? (Y/N):\n> ");

			if (character == 'n' || character == 'N') {
				std::cout << "\n��� ��� ���������� ������ �� " << portions << (portions == 1 ? " ������:" : portions > 1 &&
					portions < 5 ? " ������:" : " ������:") << std::endl;
				switch (userInput) {
				case 1:
					rec1.printIngredients(portions);
					break;

				case 2:
					rec2.printIngredients(portions);
					break;

				case 3:
					rec3.printIngredients(portions);
					break;
				}
				return 0;
			} else if (character == 'y' || character == 'Y') {
				short input;
				S:
				getDataFromUser(input, "\n�� ����:\n1. ������ �����\n2. ��������\n3. ������ �������\n4. �����\n> ");

				if (input < 1 || input > 3) {
					if (input == 4) break;
					std::cout << "������� ����� �� ������� �������� ��������� ������. �������� ������.\n";
					goto S;
				} 

				switch (input) {
				case 1:
				{
					std::string newIngredient;
					getDataFromUser(newIngredient, "\n������ ����� �����䳺��:\n> ");

					int amountOfIngredient;
					getDataFromUser(amountOfIngredient, "������ ������� �����䳺��� (�����):\n> ");

					std::cout << "\n�����䳺�� ������ ������. ��� ��������� ������ �����䳺��� �� " << portions << (portions == 1 ? " ������:" : portions > 1 &&
						portions < 5 ? " ������:" : " ������:") << std::endl;
					switch (userInput) {
					case 1:
					{
						rec1.addIngredient(rec1, newIngredient, amountOfIngredient, portions);
						rec1.printIngredients(portions);
						break;
					}

					case 2:
					{
						rec2.addIngredient(rec2, newIngredient, amountOfIngredient, portions);
						rec2.printIngredients(portions);
						break;
					}

					case 3:
					{
						rec3.addIngredient(rec3, newIngredient, amountOfIngredient, portions);
						rec3.printIngredients(portions);
						break;
					}
					}
					break;
				}

				case 2:
				{
					std::string ingredientToDelete;
					getDataFromUser(ingredientToDelete, "\n������ �����䳺�� ���� �� ������ ��������:\n> ");
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					int index = -1;

					std::cout << "\n��� ��������� ������ �����䳺��� ��� ����������:\n";
					switch (userInput) {
					case 1:
						rec1.removeIngredient(rec1, ingredientToDelete, index);
						rec1.printIngredients(portions);
						break;

					case 2:
						rec2.removeIngredient(rec2, ingredientToDelete, index);
						rec2.printIngredients(portions);
						break;

					case 3:
						rec3.removeIngredient(rec3, ingredientToDelete, index);
						rec3.printIngredients(portions);
						break;
					}
					break;
				}

				case 3:
				{
					std::string ingredientToEdit;
					getDataFromUser(ingredientToEdit, "\n������ ����� �����䳺��� ������� ����� �� ������ ������:\n> ");

					int newAmountOfIngredients;
					getDataFromUser(newAmountOfIngredients, "������ ���� ������� �����䳺���:\n> ");

					bool changed = false;

					std::cout << "\n��� ��������� ������ �� ������� ������� �����䳺��� �� " << portions
						<< (portions == 1 ? " ������:" : portions > 1 &&
							portions < 5 ? " ������:" : " ������:") << std::endl;
					switch (userInput) {
					case 1:
						rec1.editIngredient(rec1, ingredientToEdit, newAmountOfIngredients, &changed);
						rec1.printIngredients(portions);
						break;

					case 2:
						rec2.editIngredient(rec2, ingredientToEdit, newAmountOfIngredients, &changed);
						rec2.printIngredients(portions);
						break;

					case 3:
						rec3.editIngredient(rec3, ingredientToEdit, newAmountOfIngredients, &changed);
						rec3.printIngredients(portions);
						break;
					}
					break;
				}
				}
			} else {
				std::cout << "\n������� ������� ����.\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				goto M;
				break;
			}
		} while (character != 'n' && character != 'N');
	} while (userInput);
	return 0;
}

template <typename T>
void getDataFromUser(T& variable, std::string text) {
	bool validInput = false;

	while (!validInput) {
		std::cout << text;
		std::cin >> variable;

		if (isCorrectInput()) {
			validInput = true;
		}
	}
}

bool isCorrectInput() {
	if (std::cin.fail()) {
		std::cerr << "\n������� ��������� ���! ����-�����, �������� ������!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}
