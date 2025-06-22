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
			std::cerr << "Неможливо знайти інгредієнт.\n\n";
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
			std::cout << "Введено некоректну назву інгредієнта. Спробуйте ще раз.\n\n";
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

	Recipe rec1{ "Піца", {"Борошно", "Сир", "Помідори"}, {150, 100, 1} };
	Recipe rec2{ "Омлет", {"Яйця", "Помідори", "Огірки"}, {3, 2, 2} };
	Recipe rec3{ "Салат", {"Огірки", "Капуста", "Помідори"}, {3, 1, 2} };

	short userInput;
	short portions;

	do {
		B:
		getDataFromUser(userInput, "\nОберіть рецепт:\n1. " + rec1.name + "\n2. " + rec2.name + "\n3. " + rec3.name + "\n> ");

		if (userInput < 1 || userInput > 3) {
			std::cout << "Введене число не відповідає діапазону вибіркових пунктів. Повторіть спробу.\n";
			goto B;
		}

		getDataFromUser(portions, "\nВведіть кількість порцій: ");

		std::cout << "\nІнгредієнти на " << portions << (portions == 1 ? " порцію:" : portions > 1 && portions < 5
			? " порції:" : " порцій:") << std::endl;
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
			getDataFromUser(character, "Хочете змінити інгредієнти? (Y/N):\n> ");

			if (character == 'n' || character == 'N') {
				std::cout << "\nТоді ось остаточний рецепт на " << portions << (portions == 1 ? " порцію:" : portions > 1 &&
					portions < 5 ? " порції:" : " порцій:") << std::endl;
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
				getDataFromUser(input, "\nЩо саме:\n1. Додати новий\n2. Видалити\n3. Змінити кількість\n4. Вийти\n> ");

				if (input < 1 || input > 3) {
					if (input == 4) break;
					std::cout << "Введене число не відповідає діапазону вибіркових пунктів. Повторіть спробу.\n";
					goto S;
				} 

				switch (input) {
				case 1:
				{
					std::string newIngredient;
					getDataFromUser(newIngredient, "\nВведіть новий інгредієнт:\n> ");

					int amountOfIngredient;
					getDataFromUser(amountOfIngredient, "Введіть кількість інгредієнтів (число):\n> ");

					std::cout << "\nІнгредієнт успішно додано. Ось оновлений список інгредієнтів на " << portions << (portions == 1 ? " порцію:" : portions > 1 &&
						portions < 5 ? " порції:" : " порцій:") << std::endl;
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
					getDataFromUser(ingredientToDelete, "\nВведіть інгредієнт який ви хочете видалити:\n> ");
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					int index = -1;

					std::cout << "\nОсь оновлений список інгредієнтів без видаленого:\n";
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
					getDataFromUser(ingredientToEdit, "\nВведіть назву інгредієнта кількість якого ви хочете змінити:\n> ");

					int newAmountOfIngredients;
					getDataFromUser(newAmountOfIngredients, "Введіть нову кількість інгредієнта:\n> ");

					bool changed = false;

					std::cout << "\nОсь оновлений список із зміненою кількістю інгредієнтів на " << portions
						<< (portions == 1 ? " порцію:" : portions > 1 &&
							portions < 5 ? " порції:" : " порцій:") << std::endl;
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
				std::cout << "\nВведено невірний вибір.\n\n";
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
		std::cerr << "\nВведено некоректні дані! Будь-ласка, повторіть спробу!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}
