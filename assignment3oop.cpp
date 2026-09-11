#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
class ParkingBlock
{
private:
	char*** slots;
	int* slotsPerRow;
	int totalRows;
	float x_coordinate, y_coordinate;
	int countOccupied()
	{
		int count = 0;
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				if (!isempty(i, j))
					count++;
			}
		}
		return count;
	}
public:
	ParkingBlock()
	{
		slots = nullptr;
		slotsPerRow = nullptr;
		totalRows = 0;
		x_coordinate = 0.0, y_coordinate = 0.0;
	}
	ParkingBlock(int numRows)
	{
		totalRows = numRows;
		slots = new char** [numRows];
		slotsPerRow = new int[numRows];
		for (int i = 0; i < numRows; i++)
		{
			slots[i] = nullptr;
			slotsPerRow[i] = 0;
		}
		x_coordinate = 0.0, y_coordinate = 0.0;
	}
	ParkingBlock(const ParkingBlock& other)
	{
		totalRows = other.totalRows;
		x_coordinate = other.x_coordinate;
		y_coordinate = other.y_coordinate;
		slotsPerRow = new int[totalRows];
		for (int i = 0; i < *slotsPerRow; i++)
		{
			slotsPerRow[i] = other.slotsPerRow[i];
		}
		allot();
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				if (isempty(i, j))
				{
					slots[i][j] = new char[6];
					empty(i, j);
				}
				else
				{
					slots[i][j] = new char[9];
					for (int k = 0; k < 9; k++)
					{
						slots[i][j][k] = other.slots[i][j][k];
					}
				}
			}
		}
    }
	ParkingBlock& operator=(const ParkingBlock& other)
	{
		if (this == &other)
		{
			return *this;
		}
		if (slots != nullptr)
        {
			for (int i = 0; i < totalRows; i++)
			{
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					delete[]slots[i][j];
				}
				delete[] slots[i];
			}
			delete[]slots;
			slots = nullptr;
			if(slotsPerRow!=nullptr)
				delete[]slotsPerRow;
			slotsPerRow = nullptr;
        }
		totalRows = other.totalRows;
		x_coordinate = other.x_coordinate;
		y_coordinate = other.y_coordinate;
		slotsPerRow = new int[totalRows];
		for (int i = 0; i < totalRows; i++)
		{
			slotsPerRow[i] = other.slotsPerRow[i];
		}
		allot();
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				if (isempty(i, j))
				{
					slots[i][j] = new char[6];
					empty(i, j);
				}
				else
				{
					slots[i][j] = new char[9];
					for (int k = 0; k < 9; k++)
					{
						slots[i][j][k] = other.slots[i][j][k];
					}
				}
			}
		}
		return *this;
	}
	ParkingBlock(ParkingBlock&& other)
	{
		totalRows = other.totalRows;
		other.totalRows = 0;
		x_coordinate = other.x_coordinate;
		other.x_coordinate = 0;
		y_coordinate = other.y_coordinate;
		other.y_coordinate = 0;
        slotsPerRow = other.slotsPerRow;
		other.slotsPerRow = nullptr;
		slots = other.slots;
		other.slots = nullptr;
	}
	ParkingBlock& operator=(ParkingBlock&& other)
	{
		if (this == &other)
		{
			return *this;
		}
		if (slots != nullptr)
		{
			for (int i = 0; i < totalRows; i++)
			{
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					delete[]slots[i][j];
				}
				delete[] slots[i];
			}
			delete[]slots;
			slots = nullptr;
			if (slotsPerRow != nullptr)
				delete[]slotsPerRow;
			slotsPerRow = nullptr;
		}
		totalRows = other.totalRows;
		other.totalRows = 0;
		x_coordinate = other.x_coordinate;
		other.x_coordinate = 0;
		y_coordinate = other.y_coordinate;
		other.y_coordinate = 0;
		slotsPerRow = other.slotsPerRow;
		other.slotsPerRow = nullptr;
		slots = other.slots;
		other.slots = nullptr;
		return *this;
	}
	void empty(int row, int s)
	{
		slots[row][s] = new char[6];
		char* empty = new char[6];
		empty[0] = 'E', empty[1] = 'M', empty[2] = 'P', empty[3] = 'T', empty[4] = 'Y', empty[5] = '\0';
		for (int i = 0; i < 6; i++)
			slots[row][s][i] = empty[i];
		delete[]empty;
	}
	bool isempty(int row, int s)
	{

		char* E = new char[6];
		E[0] = 'E', E[1] = 'M', E[2] = 'P', E[3] = 'T', E[4] = 'Y', E[5] = '\0';
		for (int i = 0; i < 6; i++)
		{
			if (slots[row][s][i] != E[i])
				return false;
		}
		delete[]E;
		return true;
	}
	void allot()
	{
		slots = new char** [totalRows];
		for (int i = 0; i < totalRows; i++)
		{
			slots[i] = new char* [slotsPerRow[i]];
		}
	}
	void parkingstructure()
	{
		cout << "Enter number of rows :";
		cin >> totalRows;
		slotsPerRow = new int[totalRows];
		for (int i = 0; i < totalRows; i++)
		{
			cout << "\nEnter number of slots for " << i << "th row";
			cin >> slotsPerRow[i];
		}
		allot();
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				empty(i, j);
			}
		}

	}
	void parkcar(int row, int slot, char* vehiclenumber)
	{
		if (row <= 0 || row > totalRows && slot <= 0 || slot > slotsPerRow[row - 1])
		{
			cout << "\nOut of bound ";
			return;
		}
		else if (isempty(row - 1, slot - 1))
		{
			delete[]slots[row - 1][slot - 1];
			slots[row - 1][slot - 1] = new char[9];
			for (int i = 0; i < 9; i++)
			{
				slots[row - 1][slot - 1][i] = vehiclenumber[i];
			}
			cout << "\nVehicle parked ";
		}
		else
			cout << "\nSlot is not empty ";
	}
	void removecar(int row, int slot)
	{
		if (row <= 0 || row > totalRows && slot <= 0 || slot > slotsPerRow[row - 1])
		{
			cout << "\nOut of bound ";
			return;
		}
		else if (!isempty(row - 1, slot - 1))
		{
			delete[]slots[row - 1][slot - 1];
			empty(row - 1, slot - 1);
			cout << "\nVehicle removed ";
		}
		else
			cout << "\nSlot is already empty ";
	}
	void displayBlock(int n)
	{
		cout << endl;

		for (int i = 0; i < totalRows; i++)
		{
			cout << "X :" << x_coordinate << " Y :" << y_coordinate << " ";
			cout << "Row " << i + 1 << " :" << endl;
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				cout << slots[i][j] << "   ";
			}
			cout << endl;
		}
	}
	void resizeSlots(int row, int newsize, bool flag)
	{

		if (row <= 0 || row > totalRows)
		{
			cout << "\nOut of bound ";
			return;
		}
		else if (flag == true)//increase slots 
		{
			char** newslot = new char* [newsize];
			for (int i = 0; i < slotsPerRow[row - 1]; i++)
			{
				if (isempty(row - 1, i))
				{
					newslot[i] = new char[6];
					for (int j = 0; j < 6; j++)
						newslot[i][j] = slots[row - 1][i][j];
				}
				else
				{
					newslot[i] = new char[9];
					for (int j = 0; j < 9; j++)
						newslot[i][j] = slots[row - 1][i][j];
				}
			}
			for (int i = slotsPerRow[row - 1]; i < newsize; i++)
			{
				newslot[i] = new char[6];
				newslot[i][0] = 'E', newslot[i][1] = 'M', newslot[i][2] = 'P', newslot[i][3] = 'T', newslot[i][4] = 'Y', newslot[i][5] = '\0';
			}
			for (int i = 0; i < slotsPerRow[row - 1]; i++)
				delete[]slots[row - 1][i];
			delete[]slots[row - 1];
			slots[row - 1] = newslot;
			slotsPerRow[row - 1] = newsize;
		}
		else
		{
			char** newslot = new char* [newsize];
			for (int i = newsize - 1; i < slotsPerRow[row - 1]; i++)
			{
				if (!isempty(row - 1, i))
				{
					cout << "\n Vehicle exists ";
					return;
				}
			}
			for (int i = 0; i < newsize; i++)
			{
				if (isempty(row - 1, i))
				{
					newslot[i] = new char[6];
					for (int j = 0; j < 6; j++)
						newslot[i][j] = slots[row - 1][i][j];
				}
				else
				{
					newslot[i] = new char[9];
					for (int j = 0; j < 9; j++)
						newslot[i][j] = slots[row - 1][i][j];
				}

			}
			for (int i = 0; i < slotsPerRow[row - 1]; i++)
				delete[]slots[row - 1][i];
			delete[]slots[row - 1];
			slots[row - 1] = newslot;
			slotsPerRow[row - 1] = newsize;
		}
	}
	int* searchVehicle(char* vehicleNumber)
	{
		int* A = new int[2];
		for (int i = 0; i < totalRows; i++)
		{
			bool flag = true;
			int k = 0;
			int j;
			for (j = 0; j < slotsPerRow[i]; j++)
			{
				if (slots[i][j][k] != vehicleNumber[k++])
				{
					flag = false;
					break;
				}
			}
			if (flag == true)
				A[0] = i, A[1] = j;
			return A;
		}
	}
	void emptyRow(int row)
	{
		for (int i = 0; i < slotsPerRow[row - 1]; i++)
		{
			empty(row - 1, i);
		}
	}
	void emptyBlock()
	{
		for (int i = 0; i < totalRows; i++)
		{
			emptyRow(i + 1);
		}
	}
	void transferVehicles(ParkingBlock& source)
	{
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
				delete[] slots[i][j];

			delete[] slots[i];
		}

		delete[] slots;
		delete[] slotsPerRow;

		totalRows = source.totalRows;

		slotsPerRow = new int[totalRows];
		for (int i = 0; i < totalRows; i++)
			slotsPerRow[i] = source.slotsPerRow[i];

		slots = new char** [totalRows];
		for (int i = 0; i < totalRows; i++)
			slots[i] = new char* [slotsPerRow[i]];

		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				if (source.isempty(i, j))
				{
					empty(i, j);
				}
				else
				{
					slots[i][j] = new char[9];
					for (int k = 0; k < 9; k++)
						slots[i][j][k] = source.slots[i][j][k];
				}
			}
		}
	}
	void smartAllocate(char* vehicleNumber, int desiredBlockIndex)
	{
		double minDist = 10000;
		int selRow = -1, selSlot = -1;

		for (int j = 0; j < totalRows; j++)
		{
			for (int k = 0; k < slotsPerRow[j]; k++)
			{
				if (isempty(j, k))   
				{
					double slotX = x_coordinate + k * 16;
					double slotY = y_coordinate + j * 8;

					double dist = sqrt((slotX - x_coordinate) * (slotX - x_coordinate) +
						(slotY - y_coordinate) * (slotY - y_coordinate));

					if (dist < minDist)
					{
						minDist = dist;
						selRow = j;
						selSlot = k;
					}
				}
			}
		}

		if (selRow != -1 && selSlot != -1)
		{
			int l = 0;

			while (vehicleNumber[l] != '\0')
			{
				slots[selRow][selSlot][l] = vehicleNumber[l];
				l++;
			}

			slots[selRow][selSlot][l] = '\0';

			cout << "Car parked at Row " << selRow + 1
				<< " Slot " << selSlot + 1 << endl;
		}
		else
		{
			cout << "No empty slots available in this block\n";
		}
	}
	void addRows(int n)
	{
		int oldRows = totalRows;
		int newRows = totalRows + n;

		char*** newSlots = new char** [newRows];
		int* newSlotsPerRow = new int[newRows];

		for (int i = 0; i < oldRows; i++)
		{
			newSlots[i] = slots[i];
			newSlotsPerRow[i] = slotsPerRow[i];
		}

		for (int i = oldRows; i < newRows; i++)
		{
			newSlots[i] = nullptr;
			newSlotsPerRow[i] = 0;
		}

		delete[] slots;
		delete[] slotsPerRow;

		slots = newSlots;
		slotsPerRow = newSlotsPerRow;
		totalRows = newRows;
	}

	void addSlots(int row, int n)
	{
		slotsPerRow[row] = n;
		slots[row] = new char* [n];

		for (int i = 0; i < n; i++)
		{
			empty(row, i);   
		}
	}

	void setCoordinates(float x, float y)
	{
		x_coordinate = x;
		y_coordinate = y;
	}
	friend ostream& operator<<(ostream& out, const ParkingBlock& other)
	{
		out << "X :" << other.x_coordinate << " Y :" << other.y_coordinate << " ";
		for (int i = 0; i < other.totalRows; i++)
		{
			out << "Row " << i + 1 << " :" << endl;
			for (int j = 0; j < other.slotsPerRow[i]; j++)
			{
				out << other.slots[i][j] << "   ";
			}
			out << endl;
		}
		return out;
    }
	friend istream& operator>>(istream& in, ParkingBlock& other)
	{
		if (other.slots)
		{
			for (int i = 0; i < other.totalRows; i++)
			{
				for (int j = 0; j < other.slotsPerRow[i]; j++)
				{
					delete[]other.slots[i][j];
				}
				delete[] other.slots[i];
			}
			delete[]other.slots;
			other.slots = nullptr;
			delete[]other.slotsPerRow;
			other.slotsPerRow = nullptr;
		}
		cout << "Enter total number of rows :";
		in >> other.totalRows;
		other.addRows(other.totalRows);
		int* slotsPerRow = new int[other.totalRows];
		for (int i = 0; i < other.totalRows; i++)
		{
			in >> other.slotsPerRow[i];
		}
		for (int i = 0; i < other.totalRows; i++)
		{
			for (int j = 0; j < other.slotsPerRow[i]; j++)
			{
				other.addSlots(i, j);
			}
		}
		return in;
	}
	bool operator==(const ParkingBlock& other)const
	{
		if (totalRows != other.totalRows)
		{
			return false;
		}
		for (int i = 0; i < other.totalRows; i++)
		{
			if (slotsPerRow[i] != other.slotsPerRow[i])
			{
				return false;
			}
		}
		for (int i = 0; i < other.totalRows; i++)
		{
			for (int j = 0; j < other.slotsPerRow[i]; j++)
			{
				if (slots[i][j] != other.slots[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
	bool operator!=(const ParkingBlock& other)const
	{
		return !(this == &other);
	}
	bool operator > (ParkingBlock& other)
	{
		int n1 = this->countOccupied();
		int n2 = other.countOccupied();
		if (n1 > n2)
		{
			return true;
		}
		return false;
	}
	bool operator < (ParkingBlock& other)
	{
		return !(this > &other);
	}
	void addrow()
	{
		int* newSlotsPerRow = new int[totalRows + 1];

		for (int i = 0; i < totalRows; i++)
			newSlotsPerRow[i] = slotsPerRow[i];
		newSlotsPerRow[totalRows] = 1;
		char*** newSlots = new char** [totalRows + 1];
		for (int i = 0; i < totalRows; i++)
		{
			newSlots[i] = new char* [newSlotsPerRow[i]];

			for (int j = 0; j < newSlotsPerRow[i]; j++)
			{
				if (isempty(i, j))
				{
					newSlots[i][j] = new char[6];
					for (int k = 0; k < 6; k++)
						newSlots[i][j][k] = slots[i][j][k];
				}
				else
				{
					newSlots[i][j] = new char[9];
					for (int k = 0; k < 9; k++)
						newSlots[i][j][k] = slots[i][j][k];
				}
			}
		}
		newSlots[totalRows] = new char* [1];
		newSlots[totalRows][0] = new char[6];

		for (int k = 0; k < 6; k++)
			newSlots[totalRows][0][k] = '\0';
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
				delete[] slots[i][j];

			delete[] slots[i];
		}
		delete[] slots;
		delete[] slotsPerRow;
		slots = newSlots;
		slotsPerRow = newSlotsPerRow;

		totalRows++;
	}
	char** addslot(int row)
	{
		int newSize = slotsPerRow[row] + 1;

		char** newRow = new char* [newSize];
		for (int i = 0; i < slotsPerRow[row]; i++)
		{
			if (isempty(row, i))
			{
				newRow[i] = new char[6];
				for (int j = 0; j < 6; j++)
					newRow[i][j] = slots[row][i][j];
			}
			else
			{
				newRow[i] = new char[9];
				for (int j = 0; j < 9; j++)
					newRow[i][j] = slots[row][i][j];
			}
		}
		newRow[newSize - 1] = new char[6];
		for (int j = 0; j < 6; j++)
			newRow[newSize - 1][j] = '\0';
		for (int i = 0; i < slotsPerRow[row]; i++)
			delete[] slots[row][i];

		delete[] slots[row];
		slotsPerRow[row] = newSize;

		return newRow;
	}
	void mergeVehicles(ParkingBlock& source)
	{
		while (totalRows < source.totalRows)
		{
			addrow();
		}
		for (int i = 0; i < source.totalRows; i++)
		{
			for (int j = 0; j < source.slotsPerRow[i]; j++)
			{
				if (!source.isempty(i, j))
				{
					bool placed = false;

					for (int k = 0; k < slotsPerRow[i]; k++)
					{
						if (isempty(i, k))
						{
							slots[i][k] = new char[9];

							for (int x = 0; x < 9; x++)
							{
								slots[i][k][x] = source.slots[i][j][x];
							}

							placed = true;
							break;
						}
					}
					if (!placed)
					{
						slots[i] = addslot(i);
						slots[i][slotsPerRow[i] - 1] = new char[9];

						for (int x = 0; x < 9; x++)
						{
							slots[i][slotsPerRow[i] - 1][x] = source.slots[i][j][x];
						}
					}
				}
			}
		}
	}
	ParkingBlock operator+(const ParkingBlock& other)
	{
		ParkingBlock result = *this;
		ParkingBlock temp = other;
		result.mergeVehicles(temp);
		return result;
	}
	ParkingBlock operator-(ParkingBlock& other) 
	{
		ParkingBlock result = *this;
		for (int i = 0; i < other.totalRows; i++)
		{
			for (int j = 0; j < other.slotsPerRow[i]; j++)
			{
				if (!other.isempty(i, j))
				{
					for (int r = 0; r < result.totalRows; r++)
					{
						for (int s = 0; s < result.slotsPerRow[r]; s++)
						{
							if (!result.isempty(r, s))
							{
								bool match = true;
								for (int k = 0; k < 9; k++)
								{
									if (result.slots[r][s][k] != other.slots[i][j][k])
									{
										match = false;
										break;
									}
								}
								if (match)
								{
									result.empty(r, s);
									break;
								}
							}
						}
					}
				}
			}
		}

		return result;
	}
	ParkingBlock& operator +=(char * vehicle)
	{
		smartAllocate(vehicle, 0);
		return *this;
	}
	ParkingBlock& operator-=( ParkingBlock& other)
	{
		*this = *this - other;
		return *this;
	}
	ParkingBlock& operator-=(const char* vehicle)
	{
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				if (!isempty(i, j))
				{
					bool match = true;
					for (int k = 0; k < 9; k++)
					{
						if (slots[i][j][k] != vehicle[k])
						{
							match = false;
							break;
						}
					}
					if (match)
					{
						empty(i, j);   
						return *this; 
					}
				}
			}
		}
		cout << "Vehicle not found\n";
		return *this;
	}
	ParkingBlock& operator++()
	{
		ParkingBlock B = *this;
		B.addRows(1);
		B.addSlots(B.totalRows - 1, 4);
		for (int i = 0; i < 4; i++)
		{
			B.empty(B.totalRows - 1, i);
		}
		*this = std::move(B);
		return *this;
	}
	ParkingBlock& operator--()
	{
		int count = 0;
		for (int i = 0; i < slotsPerRow[totalRows - 1]; i++)
		{
			if (isempty(totalRows - 1, i))
				count++;
		}
		if (count == slotsPerRow[totalRows - 1])
		{
			ParkingBlock B;
			B.totalRows = totalRows - 1;
			B.slotsPerRow = new int[B.totalRows];
			for (int i = 0; i < B.totalRows; i++)
			{
				B.slotsPerRow[i] = slotsPerRow[i];
			}
			B.allot();
			for (int i = 0; i < B.totalRows; i++)
			{
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					if (isempty(i, j))
					{
						B.slots[i][j] = new char[6];
						for (int k = 0; k < 6; k++)
							B.slots[i][j][k] = slots[i][j][k];
					}
					else
					{
						B.slots[i][j] = new char[9];
						for (int k = 0; k < 9; k++)
							B.slots[i][j][k] = slots[i][j][k];
					}
				}
			}
			*this = std::move(B);
		}
		else
		{
			cout << "Error! Last Row Contain a Vehicle\n";
		}
		return *this;
	}
	ParkingBlock operator++(int)
	{
		ParkingBlock B = *this;
		++(*this);
		return B;
	}
	ParkingBlock operator--(int)
	{
		ParkingBlock B = *this;
		--(*this);
		return B;
	}
	void coordinate(float x, float y)
	{
		x_coordinate = x, y_coordinate = y;
	}
	~ParkingBlock()
	{

		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				delete[]slots[i][j];
			}
			delete[] slots[i];
		}
		delete[]slots;
		slots = nullptr;
		delete[]slotsPerRow;
		slotsPerRow = nullptr;
	}
};
ParkingBlock* loadParkingLot(string filename, int& totalBlocks)
{
	ifstream file(filename);
	if (!file)
	{
		cout << "\nFile not found!" << endl;
		totalBlocks = 0;
		return nullptr;
	}
	file >> totalBlocks;
	ParkingBlock* blocks = new ParkingBlock[totalBlocks];
	for (int i = 0; i < totalBlocks; i++)
	{
		file >> blocks[i];
	}
	file.close();
	return blocks;
}
void loadBlockCoordinates(string filename, ParkingBlock* blocks, int totalBlocks)
{
	ifstream file(filename);
	if (!file)
	{
		cout << "\nFile not found!" << endl;
		return;
	}
	float x, y;
	int count = 0;
	while (file >> x >> y && count < totalBlocks)
	{
		blocks[count++].coordinate(x, y);
	}
	file.close();


	cout << "\nBlock Coordinates Loaded Successfully:";
	for (int i = 0; i < totalBlocks; i++)
	{
		cout << "\nBlock " << i + 1 << ":";
	}
}
void menu()
{
	cout << "\n--------- PARKING SYSTEM MENU ---------\n";
	cout << "0  - Initialize (load from file / manual)\n";
	cout << "1  - Park a vehicle\n";
	cout << "2  - Remove a vehicle\n";
	cout << "3  - Display full system\n";
	cout << "4  - Resize slots in a row\n";
	cout << "5  - Search for a vehicle\n";
	cout << "6  - Empty a row\n";
	cout << "7  - Empty a block\n";
	cout << "8  - Transfer vehicles between blocks\n";
	cout << "9  - Smart park (+=)\n";
	cout << "10 - Remove vehicles of one block from another\n";
	cout << "11 - Remove specific vehicle\n";
	cout << "12 - Add row (++block)\n";
	cout << "13 - Remove last empty row (--block)\n";
	cout << "14 - Compare two blocks\n";
	cout << "15 - Merge two blocks (+)\n";
	cout << "16 - Subtract blocks (-)\n";
	cout << "17 - Load block coordinates\n";
	cout << "18 - Merge vehicles (bonus)\n";
	cout << "19 - Exit\n";
	cout << "Enter choice: ";
}
int main()
{
	int totalBlocks;
	cout << "Enter number of parking blocks: ";
	cin >> totalBlocks;

	ParkingBlock* blocks = new ParkingBlock[totalBlocks];
	for (int i = 0; i < totalBlocks; i++)
	{
		cout << "\nInitializing Block " << i + 1 << endl;
		blocks[i].parkingstructure();

		float x, y;
		cout << "Enter coordinates (x y): ";
		cin >> x >> y;
		blocks[i].setCoordinates(x, y);
	}

	int choice;

	do
	{
		menu();
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int b, r, s;
			char vehicle[10];
			cout << "Block Row Slot: ";
			cin >> b >> r >> s;
			cout << "Vehicle number: ";
			cin >> vehicle;
			blocks[b - 1].parkcar(r, s, vehicle);
			break;
		}

		case 2:
		{
			int b, r, s;
			cout << "Block Row Slot: ";
			cin >> b >> r >> s;
			blocks[b - 1].removecar(r, s);
			break;
		}

		case 3:
		{
			for (int i = 0; i < totalBlocks; i++)
			{
				cout << "\nBlock " << i + 1 << ":\n";
				cout << blocks[i];
			}
			break;
		}

		case 4:
		{
			int b, r, newSize;
			bool flag;
			cout << "Block Row NewSize Increase(1)/Decrease(0): ";
			cin >> b >> r >> newSize >> flag;
			blocks[b - 1].resizeSlots(r, newSize, flag);
			break;
		}

		case 5:
		{
			int b;
			char vehicle[10];
			cout << "Block: ";
			cin >> b;
			cout << "Vehicle number: ";
			cin >> vehicle;

			int* res = blocks[b - 1].searchVehicle(vehicle);
			cout << "Found at Row " << res[0] + 1
				<< " Slot " << res[1] + 1 << endl;
			delete[] res;
			break;
		}

		case 6:
		{
			int b, r;
			cin >> b >> r;
			blocks[b - 1].emptyRow(r);
			break;
		}

		case 7:
		{
			int b;
			cin >> b;
			blocks[b - 1].emptyBlock();
			break;
		}

		case 8:
		{
			int src, dest;
			cin >> src >> dest;
			blocks[dest - 1].transferVehicles(blocks[src - 1]);
			break;
		}

		case 9:
		{
			int b;
			char vehicle[10];
			cin >> b >> vehicle;
			blocks[b - 1] += vehicle;
			break;
		}

		case 10:
		{
			int b1, b2;
			cin >> b1 >> b2;
			blocks[b1 - 1] -= blocks[b2 - 1];
			break;
		}

		case 11:
		{
			int b;
			char vehicle[10];
			cin >> b >> vehicle;
			blocks[b - 1] -= vehicle;
			break;
		}

		case 12:
		{
			int b;
			cin >> b;
			++blocks[b - 1];
			break;
		}

		case 13:
		{
			int b;
			cin >> b;
			--blocks[b - 1];
			break;
		}

		case 14:
		{
			int b1, b2;
			cin >> b1 >> b2;

			if (blocks[b1 - 1] == blocks[b2 - 1])
				cout << "Blocks are equal\n";
			else if (blocks[b1 - 1] > blocks[b2 - 1])
				cout << "Block " << b1 << " has more vehicles\n";
			else
				cout << "Block " << b2 << " has more vehicles\n";

			break;
		}

		case 15:
		{
			int b1, b2;
			cin >> b1 >> b2;
			ParkingBlock result = blocks[b1 - 1] + blocks[b2 - 1];
			cout << result;
			break;
		}

		case 16:
		{
			int b1, b2;
			cin >> b1 >> b2;
			ParkingBlock result = blocks[b1 - 1] - blocks[b2 - 1];
			cout << result;
			break;
		}

		case 17:
		{
			float x, y;
			int b;
			cout << "Block and coordinates: ";
			cin >> b >> x >> y;
			blocks[b - 1].setCoordinates(x, y);
			break;
		}

		case 18:
		{
			int b1, b2;
			cout << "Enter source block and destination block :\n";
			cin >> b1 >> b2;
			blocks[b1 - 1].mergeVehicles(blocks[b2 - 1]);
			break;
		}

		case 19:
			cout << "Exiting...\n";
			break;

		default:
			cout << "Invalid choice!\n";
 
		}

	} while (choice != 19);

	delete[] blocks;
	return 0;
}
