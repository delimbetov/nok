/*--------------------------------------------------------------------------*/
#include <limits>
/*--------------------------------------------------------------------------*/
#include "Queue.h"
/*--------------------------------------------------------------------------*/

/***********************************************/
int main(int argc, char* argv[]) //как аргумент можно передать желаемое количество потоков [1, 2^16)
{
	try
	{
		ThreadInt threadNumber;
		Queue queue;
		NumberInt number;
		int32_t numOfNums;

		//разбор арг-ов командной строки (должно быть
		switch(argc)
		{
			case(2):
			{
				try
				{
					numOfNums = std::stoi(argv[1]);
				}
				catch(const std::invalid_argument&)
				{
					THROW("Аргумент не число, а должен быть");
				}

				if(numOfNums < 0)
					THROW("Неправильный аргумент; Допустимые значения [0, " << std::numeric_limits<decltype(numOfNums)>::max() << "]\n");

				threadNumber = std::thread::hardware_concurrency() - 1; // -1 - текущий

				break;
			}
			case(3):
			{
				int64_t temp;

				try
				{
					numOfNums = std::stoi(argv[1]);
				}
				catch(const std::invalid_argument&)
				{
					THROW("Аргумент не число, а должен быть");
				}

				if(numOfNums < 0)
					THROW("Неправильный аргумент; Допустимые значения [0, " << std::numeric_limits<decltype(numOfNums)>::max() << "]\n");

				try
				{
					temp = std::stoi(argv[2]);
				}
				catch(const std::invalid_argument&)
				{
					THROW("Аргумент не число, а должен быть");
				}

				if(temp > std::numeric_limits<decltype(threadNumber)>::max() || temp < 1)
					THROW("Неправильный аргумент; Допустимые значения [1, " << std::numeric_limits<decltype(threadNumber)>::max() << "]\n");

				threadNumber = temp;

				break;
			}
			default:
			{
				THROW("Неправильное количество аргументов");
			}
		}

		D("Используемое количество потоков=" << threadNumber);
		queue.setThreadNumber(threadNumber);

		D("Начало считывания " << numOfNums << " чисел");
		//считывание, пока дают числа
		while(numOfNums--)
		{
			std::cin >> number;

			if(number > maxNumber || number < 0)
				THROW("Неправильное число; Допустимые значения [0, " << maxNumber << "]");

			queue.add(number);
		}

		D("Считывание окончено");
		//ожидание выполнения всех потоков
		queue.join();
		//TODO вывести результаты
	}
	catch(const std::exception& e)
	{
		ERR("Ошибка при выполнении программы: " << e.what());
		return 1;
	}
	catch(...)
	{
		ERR("Неизвестная ошибка при выполнении программы");
		return 2;
	}

	return 0;
}

