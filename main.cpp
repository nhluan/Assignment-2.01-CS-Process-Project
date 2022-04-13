#include <iostream> 
#include <string>
#include <sstream>
#include <queue>
#include <fstream>
#include <math.h>

using namespace std;

// declare: 
class Process;
class processManagement;
class fileManager;
string dataQuantum;

// define: 
class Process {
private:
    string _nameProcess;
    int _arrivalTime;
    int _burstTime;
    int _priority;

    // FCFS
    int _totalTimeFCFS;
    int _waittingTimeFCFS;

    // RR
    int _totalTimeRR;
    int _waittingTimeRR = 0;
    int _timeReal = 0;
    int _checkStart = 0;
    vector<int> Time;
    int _timeStop = 0;
    int _timeStart = 0;
    int _checkArrivalTime = 0;

    // SJF
    int _totalTimeSJF;
    int _waittingTimeSJF;

public:

    string getNameProcess() {
        return _nameProcess;
    }

    int getArrivalTime() {
        return _arrivalTime;
    }

    int getBurstTime() {
        return _burstTime;
    }

    int getPriority() {
        return _priority;
    }

    int getTotalTimeFCFS() {
        return _totalTimeFCFS;
    }

    int getWaittingTimeFCFS() {
        return _waittingTimeFCFS;
    }

    int getTotalTimeRR() {
        return _totalTimeRR;
    }

    int getWaittingTimeRR() {
        return _waittingTimeRR;
    }

    int getTimeReal() {
        return _timeReal;
    }

    int getTimeStop() {
        return _timeStop;
    }

    int getTimeStart() {
        return _timeStart;
    }

    int getCheckArrivalTime() {
        return _checkArrivalTime;
    }

    int getTotalTimeSJF() {
        return _totalTimeSJF;
    }

    int getWaittingTimeSJF() {
        return _waittingTimeSJF;
    }

    int getCheckStart() {
        return _checkStart;
    }

    vector<int> getTime() {
        return Time;
    }

    void setFullInformation(string data) {
        string nameProcess;
        int arrivalTime;
        int burstTime;
        int priority;
        string arrivalTimeRow;
        string burstTimeRow;
        string priorityRow;

        stringstream ss(data);
        getline(ss, nameProcess, ' ');
        getline(ss, arrivalTimeRow, ' ');
        getline(ss, burstTimeRow, ' ');
        getline(ss, priorityRow);

        arrivalTime = stoi(arrivalTimeRow);
        burstTime = stoi(burstTimeRow);
        priority = stoi(priorityRow);

        _nameProcess = nameProcess;
        _arrivalTime = arrivalTime;
        _burstTime = burstTime;
        _priority = priority;
        _waittingTimeSJF = 0;
    }

    void setBurstTime(int value) { _burstTime = value; }
    void setTotalTimeFCFS(int value) {
        _totalTimeFCFS = value;
    }

    void setWaittingTimeFCFS(int value) {
        _waittingTimeFCFS = value;
    }

    void setTotalTimeRR(int value) {
        _totalTimeRR = value;
    }

    void setWaittingTimeRR(int value) {
        _waittingTimeRR = _waittingTimeRR + value;
    }

    void setTimeReal(int value) {
        _timeReal = _timeReal + value;
    }

    void setCheckStart(int value) {
        _checkStart = value;
    }

    void setTotalTimeSJF(int value) {
        _totalTimeSJF = value;
    }

    void setWaittingTimeSJF(int value) {
        _waittingTimeSJF = value;
    }

    int convertStringNameProcess(string value) {
        string result = "";
        for (int i = 1; i < value.length(); i++) {
            string temp;
            temp.push_back(value[i]);
            result = result + temp;
        }
        int resultReturn;
        resultReturn = stoi(result);

        return resultReturn;
    }

    void setTimeStop(int value) {
        _timeStop = value;
    }

    void setTimeStart(int value) {
        _timeStart = value;
    }

    void setCheckArrivalTime(int value) {
        _checkArrivalTime = value;
    }

    void setTime(int value) {
        Time.push_back(value);
    }

    void deleteTime() {
        Time.erase(Time.begin());
    }
    Process& operator= (const Process& x) {
        _nameProcess = x._nameProcess;
        _arrivalTime = x._arrivalTime;
        _burstTime = x._burstTime;
        _priority = x._priority;

        _totalTimeFCFS = x._totalTimeFCFS;
        _waittingTimeFCFS = x._waittingTimeFCFS;

        _totalTimeRR = x._totalTimeRR;
        _waittingTimeRR = x._waittingTimeRR;

        _totalTimeSJF = x._totalTimeSJF;
        _waittingTimeSJF = x._waittingTimeSJF;

        return *this;
    }
};

class processManagement {
protected:
    vector<Process> _processes;
    int _quantum;
public:

    string showProcessFCFS() {
        string result = "0";
        int timeStart = _processes[0].getBurstTime();
        string temp;
        string characterLink = "-";
        result = result + characterLink + _processes[0].getNameProcess() + characterLink + to_string(_processes[0].getBurstTime())
            + characterLink + _processes[1].getNameProcess();
        for (int i = 1; i < _processes.size(); i++) {
            timeStart = timeStart + _processes[i].getBurstTime();
            if (i == _processes.size() - 1) {
                temp = characterLink + to_string(timeStart);
                result = result + temp;
                break;
            }
            temp = characterLink + to_string(timeStart) + characterLink + _processes[i + 1].getNameProcess();
            result = result + temp;
        }

        return result;
    }

    void waittingTimeFCFS() {
        int timeStartProcess = _processes[0].getBurstTime();
        _processes[0].setWaittingTimeFCFS(0);
        for (int i = 1; i < _processes.size(); i++) {
            timeStartProcess = timeStartProcess + _processes[i].getBurstTime();
            int wt;
            wt = timeStartProcess - _processes[i].getArrivalTime() - _processes[i].getBurstTime();
            _processes[i].setWaittingTimeFCFS(wt);
        }
    }
    void totalTimeFCFS() {
        for (int i = 0; i < _processes.size(); i++) {
            int tt = _processes[i].getWaittingTimeFCFS() + _processes[i].getBurstTime();
            _processes[i].setTotalTimeFCFS(tt);
        }
    }

public: // RR
    string showProcessRR() {
        int quantum = this->getQuantum();
        queue<Process> RR;
        //RR.push(_processes[0]); 
        string result = "";
        string characterLink = "-";
        int timeStart = quantum;
        for (int i = 0; i < _processes.size(); i++) {
            if (_processes[i].getArrivalTime() < timeStart) {
                //cout << i << endl; 
                RR.push(_processes[i]);
                // 1 da duoc them vao queue de xu li 
                // 0 chua tung them vao va cho den arrival time du moi vao 
                _processes[i].setCheckStart(1);
            }
        }
        int i = 0;
        int iNew;
        // chi co mot process dang con chay 
        int checkOnlyProcess = 0;
        int posOnlyProcessStart;
        // neu da chay het chuong trinh => checkEnd = 1
        int checkEnd = 0;
        while (RR.empty() != true) {
            for (int pos = 0; pos < _processes.size(); pos++) {
                if (_processes[pos].getCheckStart() == 0 && _processes[pos].getTimeReal() < i) {
                    RR.push(_processes[pos]);
                    _processes[pos].setCheckStart(1);
                }
            }
            Process need = RR.front();
            RR.pop();
            if (checkEnd == 0) {
                // chuong trinh van chay theo tien do binh thuong
                // chua het thoi gian chay 
                result = result + to_string(i) + characterLink + need.getNameProcess() + characterLink;
                for (int j = 0; j < _processes.size(); j++) {
                    if (need.getNameProcess().compare(_processes[j].getNameProcess()) == 0) {
                        _processes[j].setTime(i);
                        break;
                    }
                }
                i = i + quantum;
            }
            else {
                // truong hop Process ket thuc som hon quantum 
                result = result + to_string(iNew) + characterLink + need.getNameProcess() + characterLink;
                for (int j = 0; j < _processes.size(); j++) {
                    if (need.getNameProcess().compare(_processes[j].getNameProcess()) == 0) {
                        _processes[j].setTime(iNew);
                        break;
                    }
                }
                i = iNew + quantum;
                checkEnd = 0;
            }
            for (int j = 0; j < _processes.size(); j++) {
                if (need.getNameProcess().compare(_processes[j].getNameProcess()) == 0) {
                    _processes[j].setTimeReal(quantum);
                    int k = _processes[j].getTimeReal();
                    int k1 = _processes[j].getBurstTime();
                    // Truong hop chi co duy nhat 1 process con dang chay 
                    if (RR.size() == 0) {
                        if (checkOnlyProcess == 0) {
                            // chua tinh wt cuoi cung 
                            _processes[j].setTime(posOnlyProcessStart);
                            checkOnlyProcess = 1;
                            int start = _processes[j].getTime()[1];;
                            int end = _processes[j].getTime()[0];
                            int wt = start - end;
                            _processes[j].setWaittingTimeRR(wt);
                        }
                        else {
                            if (_processes[j].getTimeReal() < _processes[j].getBurstTime()) {
                                RR.push(_processes[j]);
                                break;
                            }
                            else {
                                // tinh thoi gian chay cuoi cung
                                checkEnd = 1;
                                // thoi gian du 
                                int redundancy = _processes[j].getTimeReal() - _processes[j].getBurstTime();
                                iNew = i - redundancy;
                            }
                        }
                    }
                    if (_processes[j].getTimeReal() < _processes[j].getBurstTime()) {
                        if (_processes[j].getCheckArrivalTime() == 0) {
                            // chua tinh thoi gian cho dau tien 
                            int wt;
                            wt = _processes[j].getTime()[0] - _processes[j].getArrivalTime();
                            _processes[j].setWaittingTimeRR(wt);
                            _processes[j].setTime(i);
                            _processes[j].deleteTime();
                            _processes[j].setCheckArrivalTime(1);
                        }
                        else {
                            // truong hop tinh toan binh thuong 
                            if (_processes[j].getTime().size() == 2) {
                                if (RR.size() != 0) {
                                    int start;
                                    int end;
                                    start = _processes[j].getTime()[1];
                                    end = _processes[j].getTime()[0];
                                    int wt;
                                    wt = start - end;
                                    _processes[j].setWaittingTimeRR(wt);
                                    _processes[j].deleteTime();
                                    _processes[j].deleteTime();

                                    _processes[j].setTime(i);
                                }
                                else {
                                    // nghia la chi con 1 process duy nhat chay 
                                    // nen se khong co waitting time
                                    RR.push(_processes[j]);
                                    break;
                                }
                            }
                        }
                        RR.push(_processes[j]);
                        break;
                    }
                    else {
                        checkEnd = 1;
                        int start;
                        int end;
                        if (_processes[j].getCheckArrivalTime() == 0) {
                            // chua tinh thoi gian cho dau tien 
                            int wt;
                            wt = _processes[j].getTime()[0] - _processes[j].getArrivalTime();
                            _processes[j].setWaittingTimeRR(wt);
                            _processes[j].setCheckArrivalTime(1);
                        }
                        // thoi gian du 
                        int redundancy = _processes[j].getTimeReal() - _processes[j].getBurstTime();
                        iNew = i - redundancy;
                        posOnlyProcessStart = iNew;
                        //_processes[j].setTime(iNew); 
                        if (_processes[j].getTime().size() == 2) {
                            int timeRealEnd;
                            timeRealEnd = quantum - redundancy;
                            start = iNew - timeRealEnd;
                            end = _processes[j].getTime()[0];
                            int wt = start - end;
                            _processes[j].setWaittingTimeRR(wt);
                        }

                    }
                }
            }
            // xac dinh thoi gian ket thuc cua ca tien trinh 
            if (RR.empty() == true) {
                result = result + to_string(iNew);
            }
        }
        return result;
    }


    void totalTimeRR() {
        for (int i = 0; i < _processes.size(); i++) {
            int result;
            result = _processes[i].getBurstTime() + _processes[i].getWaittingTimeRR();
            _processes[i].setTotalTimeRR(result);
        }
    }
    void setProcesses(vector<Process> value) {
        _processes = value;
    }

    void setQuantum(string data) {
        int quantum;
        string quantumRow;

        stringstream ss(data);
        string trash;
        getline(ss, trash, ' ');
        getline(ss, quantumRow);

        quantum = stoi(quantumRow);

        _quantum = quantum;
    }

    int getQuantum() {
        return _quantum;
    }

    void interchangeSort() {
        for (int i = 0; i <= _processes.size() - 2; i++) {
            for (int j = i + 1; j <= _processes.size() - 1; j++) {
                if (_processes[i].getArrivalTime() > _processes[j].getArrivalTime()) {
                    swap(_processes[i], _processes[j]);
                }
            }
        }
    }
    // ham chuyen doi ten string ve dang so int 
    int convertStringNameProcess(string value) {
        string result = "";
        for (int i = 1; i < value.length(); i++) {
            string temp;
            temp.push_back(value[i]);
            result = result + temp;
        }
        int resultReturn;
        resultReturn = stoi(result);

        return resultReturn;
    }

    // ham sap xep lai vector sau khi da thuc hien tinh toan xong
    // viec sap xep nay se dua theo thu tu cua process de thuc hien 
    void interchangeSortNameProcess() {
        for (int i = 0; i <= _processes.size() - 2; i++) {
            for (int j = i + 1; j <= _processes.size() - 1; j++) {
                if (_processes[i].convertStringNameProcess(_processes[i].getNameProcess()) > _processes[j].convertStringNameProcess(_processes[j].getNameProcess())) {
                    swap(_processes[i], _processes[j]);
                }
            }
        }
    }
public:
    void showData() {
        cout << "Processes: " << endl;
        for (int i = 0; i < _processes.size(); i++) {
            cout << "Process: " << _processes[i].getNameProcess() << endl;
            cout << "Arrival Time: " << _processes[i].getArrivalTime() << endl;
            cout << "CPU Burst: " << _processes[i].getBurstTime() << endl;
            cout << "Priority: " << _processes[i].getPriority() << endl;
        }
    }
    void showWaittingTimeFCFS() {
        for (int i = 0; i < _processes.size(); i++) {
            cout << _processes[i].getNameProcess() << ": " << _processes[i].getWaittingTimeFCFS() << endl;
        }
    }

    void showTotalTimeFCFS() {
        for (int i = 0; i < _processes.size(); i++) {
            cout << _processes[i].getNameProcess() << ": " << _processes[i].getTotalTimeFCFS() << endl;
        }
    }

    void showWaittingTimeRR() {
        for (int i = 0; i < _processes.size(); i++) {
            cout << _processes[i].getNameProcess() << ": " << _processes[i].getWaittingTimeRR() << endl;
        }
    }

    void showTimeStop() {
        for (int i = 0; i < _processes.size(); i++) {
            cout << _processes[i].getNameProcess() << ": " << _processes[i].getTimeStop() << endl;
        }
    }

    void showTotalTimeRR() {
        for (int i = 0; i < _processes.size(); i++) {
            cout << _processes[i].getNameProcess() << ": " << _processes[i].getTotalTimeRR() << endl;
        }
    }

public:
    // ghi du lieu vao file voi thuat toan FCFS
    void writeDataToFileFCFS() {
        ofstream write;
        write.open("FCFS.txt");
        int sumTotalTimeFCFS = 0;
        int sumWaittingTimeFCFS = 0;
        this->interchangeSortNameProcess();

        for (int i = 0; i < _processes.size(); i++) {
            sumTotalTimeFCFS += _processes[i].getTotalTimeFCFS();
            sumWaittingTimeFCFS += _processes[i].getWaittingTimeFCFS();
        }

        float averageTotalTimeFCFS;
        float averageWaittingTimeFCFS;

        averageTotalTimeFCFS = (1.00) * sumTotalTimeFCFS / _processes.size();
        averageWaittingTimeFCFS = (1.00) * sumWaittingTimeFCFS / _processes.size();
        averageTotalTimeFCFS = round(averageTotalTimeFCFS * 100) / 100;
        averageWaittingTimeFCFS = round(averageWaittingTimeFCFS * 100) / 100;

        write << "Scheduling chart:" << endl;
        write << this->showProcessFCFS() << endl;
        for (int i = 0; i < _processes.size(); i++) {
            write << _processes[i].getNameProcess() << "  TT=" << _processes[i].getTotalTimeFCFS()
                << " WT=" << _processes[i].getWaittingTimeFCFS() << endl;
        }
        write << "Average: " << "TT=" << averageTotalTimeFCFS << " WT=" << averageWaittingTimeFCFS;
        write.close();
    }

    // ghi du lieu vao file RR.txt voi thuat toan RR
    void writeDataToFileRR() {
        ofstream write;
        write.open("RR.txt");
        int sumTotalTimeRR = 0;
        int sumWaittingTimeRR = 0;

        string schedulingChart = this->showProcessRR();
        // luc nay da co gia tri cua waitting time RR
        this->totalTimeRR();
        // luc nay da co gia tri cua total time RR

        for (int i = 0; i < _processes.size(); i++) {
            sumTotalTimeRR += _processes[i].getTotalTimeRR();
            sumWaittingTimeRR += _processes[i].getWaittingTimeRR();
        }
        // da tinh xong gia tri tong cua TT va WT 

        // tinh gia tri trung binh cuar TT va WT
        float averageTotalTimeRR;
        float averageWaittingTimeRR;
        averageTotalTimeRR = (1.00) * sumTotalTimeRR / _processes.size();
        averageWaittingTimeRR = (1.00) * sumWaittingTimeRR / _processes.size();

        // lam tron hai chu so thap phan 
        averageTotalTimeRR = round(averageTotalTimeRR * 100) / 100;
        averageWaittingTimeRR = round(averageWaittingTimeRR * 100) / 100;

        // da co gia tri trung binh cua TT va WT 

        write << "Scheduling chart:" << endl;
        write << schedulingChart << endl;
        for (int i = 0; i < _processes.size(); i++) {
            write << _processes[i].getNameProcess() << ": TT=" << _processes[i].getTotalTimeRR()
                << " WT=" << _processes[i].getWaittingTimeRR() << endl;
        }

        // ghi gia tri trung binh vao file 
        write << "Average: TT=" << averageTotalTimeRR << " WT=" << averageWaittingTimeRR;
    }

public:
    string SJF() {
        stringstream builder;
        vector<Process> q = _processes;
        //sort
        for (int i = 0; i < q.size(); i++) {
            for (int j = i + 1; j < q.size(); j++) {
                if (q[i].getBurstTime() < q[j].getBurstTime()) {
                    Process t = q[i];
                    q[i] = q[j];
                    q[j] = t;
                }
            }
        }
        builder << "0~";
        int temp = 0; // t�m arrival time =0
        for (int i = 0; i < _processes.size(); i++) {
            if (_processes[i].getArrivalTime() == 0) {
                temp = i;
                break;
            }
        }
        builder << _processes[temp].getNameProcess() << "~";
        Process p = q[q.size() - 1];
        q.pop_back();
        int time = 0;
        if (_processes[temp].getNameProcess() == p.getNameProcess()) {
            _processes[temp].setWaittingTimeSJF(0);
            _processes[temp].setTotalTimeSJF(p.getBurstTime());
            time = p.getBurstTime();
            builder << time;
        }
        else {
            q[temp].setBurstTime(q[temp].getBurstTime() - p.getArrivalTime());
            time = p.getArrivalTime() + p.getBurstTime();
            _processes[temp].setWaittingTimeSJF(-p.getArrivalTime());

            for (int i = 0; i < _processes.size(); i++) {
                if (p.getNameProcess() == _processes[i].getNameProcess()) {
                    _processes[i].setWaittingTimeSJF(p.getArrivalTime());
                    _processes[i].setTotalTimeSJF(time);
                    break;
                }
            }
            builder << p.getArrivalTime() << "~" << p.getNameProcess() << "~" << time;
        }
        int n = q.size();
        for (int i = 0; i < n; i++) {
            Process p = q[q.size() - 1];
            q.pop_back();
            for (int i = 0; i < _processes.size(); i++) {
                if (p.getNameProcess() == _processes[i].getNameProcess()) {
                    _processes[i].setWaittingTimeSJF(time + _processes[i].getWaittingTimeSJF());
                    _processes[i].setTotalTimeSJF(time + p.getBurstTime());
                    break;
                }
            }
            time = time + p.getBurstTime();
            builder << "~" << p.getNameProcess() << "~" << time;
        }
        string result = builder.str();
        return result;
    }
    void writeDataToFileSJF() {
        ofstream write;
        write.open("SJF.txt");
        
        write << "Scheduling chart:" << endl;
        write << this->SJF() << endl;

        int sumTotalTimeSJF = 0;
        int sumWaittingTimeSJF = 0;
        for (int i = 0; i < _processes.size(); i++) {
            sumTotalTimeSJF += _processes[i].getTotalTimeSJF();
            sumWaittingTimeSJF += _processes[i].getWaittingTimeSJF();
        }

        float averageTotalTimeSJF;
        float averageWaittingTimeSJF;
        averageTotalTimeSJF = (1.00) * sumTotalTimeSJF / _processes.size();
        averageWaittingTimeSJF = (1.00) * sumWaittingTimeSJF / _processes.size();
        averageTotalTimeSJF = round(averageTotalTimeSJF * 100) / 100;
        averageWaittingTimeSJF = round(averageWaittingTimeSJF * 100) / 100;

        for (int i = 0; i < _processes.size(); i++) {
            write << _processes[i].getNameProcess() << "  TT=" << _processes[i].getTotalTimeSJF()
                << " WT=" << _processes[i].getWaittingTimeSJF() << endl;
        }
        write << "Average: " << "TT=" << averageTotalTimeSJF << " WT=" << averageWaittingTimeSJF;
        write.close();
    }
};

class fileManager {
public:
    vector<Process> readerData(string filePath) {
        vector<Process> result;
        ifstream reader;
        reader.open(filePath);
        string data;
        getline(reader, dataQuantum);
        while (!reader.eof()) {
            getline(reader, data);
            Process temp;
            temp.setFullInformation(data);
            result.push_back(temp);
        }
        reader.close();
        return result;
    }
};


int main() {
    string filePath = "input.txt";
    processManagement data;
    fileManager reader;
    data.setProcesses(reader.readerData(filePath));
    data.setQuantum(dataQuantum);

    // Sap xep du lieu theo thu tu Arrival time tang dan 
    data.interchangeSort();

    // FCFS: 
    data.waittingTimeFCFS();
    data.totalTimeFCFS();
    data.writeDataToFileFCFS();

    // RR: 
    data.writeDataToFileRR();

    //SJF:
    data.setProcesses(reader.readerData(filePath));
    data.writeDataToFileSJF();

    cout << "Da luu cac thong so ky thuat cua cac thuat toan RR, FCFS, SJF vao cac file" << endl; 
    cout << "FCFS.txt" << endl; 
    cout << "RR.txt" << endl; 
    cout << "SJF.txt" <<endl; 
    
    // co 1 khoang ngan de xem duoc chuong trinh 
    string enter; 
    getline(cin, enter); 

    return 1;
}
