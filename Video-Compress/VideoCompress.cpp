#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

class clsMediaAsset
{
protected:
	string _FileName;
	double _Size;
	string _outPutPath;
	string _Platform;
	string _TransformExtaintion;

public:
	virtual void ProcessAsset() = 0;
	virtual void PublishAsset() = 0;

	clsMediaAsset(string FileName, double Size, string outPutPath, string TransformExtaintion, string Platform)
	{
		_FileName = FileName;
		_Size = Size;
		_outPutPath = outPutPath;
		_TransformExtaintion = TransformExtaintion;
		_Platform = Platform;
	}
	friend class clsFinanceManager;
	friend string Platform_PUP();
	friend string outPutPath();
	friend string TransformExtaintion();
};

class clsVideoAsset : public clsMediaAsset
{
private:
	int _Bitrate;

public:
	clsVideoAsset(string FileName, double Size, string outPutPath, string TransformExtaintion, string Platform, int Bitrate)
		: clsMediaAsset(FileName, Size, outPutPath, TransformExtaintion, Platform)
	{
		_Bitrate = Bitrate;
	}

	void ProcessAsset() override
	{
		cout << "\n[FFmpeg Core]: Starting Compression for " << _FileName << _outPutPath << "..." << endl;

		// بناء سطر الأمر اللي هيروح للـ CMD// علامة الـ \" بتجبر الـ C++ يطبع علامة تنصيص حقيقية جوه النص للـ CMD
		string command = "ffmpeg -y -i \"" + _FileName + "\" -b:v " + to_string(_Bitrate) + "k -bufsize " + to_string(_Bitrate) + "k \"compressed_" + _FileName + "\"";
		cout << "Executing Command: " << command << endl;

		// 🚀 تشغيل الـ FFmpeg بجد في الويندوز
		system(command.c_str());

		cout << "[FFmpeg Core]: Compression finished! Saved as: compressed_" << _FileName << _outPutPath << endl;
	}

	void PublishAsset() override
	{
		cout << "Uploading video to " << _Platform << " Reels..." << endl;
	}

	void SetBitrate(int Bitrate)
	{
		if (Bitrate > 0)
			_Bitrate = Bitrate;
		else
			_Bitrate = 5000;
	}

	int GetBitrate() { return _Bitrate; }

	clsVideoAsset operator+(const clsVideoAsset &OutsideVideo)
	{
		string NewName = this->_FileName + " & " + OutsideVideo._FileName;
		double NewSize = this->_Size + OutsideVideo._Size;
		return clsVideoAsset(NewName, NewSize, this->_outPutPath, this->_TransformExtaintion, this->_Platform, this->_Bitrate);
	}

	friend void PrintVideoInfo(const clsVideoAsset &v1);
};

class clsAudioAsset : public clsMediaAsset
{
private:
	int _SampleRate;

public:
	clsAudioAsset(string FileName, double Size, string outPutPath, string TransformExtaintion, string Platform, int SampleRate)
		: clsMediaAsset(FileName, Size, outPutPath, TransformExtaintion, Platform)
	{
		_SampleRate = SampleRate;
	}

	void ProcessAsset() override
	{
		cout << "Enhancing Audio [" << _FileName << "] using Auphonic AI at [" << _SampleRate << "] Hz..." << endl;
	}

	void PublishAsset() override
	{
		cout << "Publishing audio to " << _Platform << endl;
	}
};

class clsFinanceManager
{
public:
	void CalculateTax(clsMediaAsset &Asset)
	{
		cout << "Hosting cost for [ " << Asset._FileName << " ] is [ " << Asset._Size * 0.5 << " ] $" << endl;
	}
};

void PrintVideoInfo(const clsVideoAsset &v1)
{
	cout << "\n____________________Video Info_________________________\n";
	cout << "File Name     : " << v1._FileName << endl;
	cout << "File Size     : " << v1._Size << endl;
	cout << "Platform      : " << v1._Platform << endl;
	cout << "Video Bitrate : " << v1._Bitrate << endl;
}

void Desin()
{
	cout << "==================================================" << endl;
	cout << "   Welcome to ZettaX Media Automation Engine      " << endl;
	cout << "==================================================" << endl;
}

vector<string> FilePath()
{
	vector<string> uploadList;
	string userFilePath;
	int TotalRounds;

	cout << "How many Videos do you want to process? ";
	cin >> TotalRounds;

	// 🔥 الحل السحري: بنمسح الـ Enter المتعلق في الذاكرة عشان الـ getline اللي جاية تشتغل صح
	cin.ignore();

	for (int i = 0; i < TotalRounds; i++)
	{
		// وضحنا للمستخدم وهو بيكتب ده الفيديو رقم كام
		cout << "\n-> Please enter the FULL path of Video [" << i + 1 << "]: ";
		getline(cin, userFilePath);

		uploadList.push_back(userFilePath);
	}

	// 2. بنرجع الـ vector كله بالكامل للـ main
	return uploadList;
}

int VideoQuality()
{

	int qualityChoice;
	int targetBitrate = 2000; // قيمة افتراضية

	// 2. اختيار الجودة (ترجمة الجودة لـ Bitrate)
	cout << "\n-> Select Target Video Quality:\n";
	cout << "1. High Quality (4000 Kbps)\n";
	cout << "2. Medium Quality (2000 Kbps)\n";
	cout << "3. Low Quality (800 Kbps)\n";
	cout << "Your choice (1-3): ";
	cin >> qualityChoice;

	switch (qualityChoice)
	{
	case 1:
		targetBitrate = 4000;
		break;
	case 2:
		targetBitrate = 2000;
		break;
	case 3:
		targetBitrate = 800;
		break;
	default:
		cout << "Invalid choice! Defaulting to Medium Quality (2000 Kbps).\n";
		targetBitrate = 2000;
	}

	return targetBitrate;
}

string outPutPath()
{
	string _outPutPath;
	string defultPath = "Downloads";

	cout << "The defuilt Save path :" << defultPath << endl;
	cout << "Please enter save loction in coumputer: " << endl;
	getline(cin, _outPutPath);
	cout << endl;

	if (_outPutPath == " ")
	{
		return defultPath;
	}
	else
	{
		return _outPutPath;
	}
}

string Platform_PUP()
{
	string _Platform;
	string defultPlatform = "Instagram";

	cout << "The defuilt Platform :" << defultPlatform << endl;
	cout << "Please enter platform puplish " << endl;
	getline(cin, _Platform);
	cout << endl;

	if (_Platform == " ")
	{
		return defultPlatform;
	}
	else
	{
		return _Platform;
	}
}

string TransformExtaintion()
{
	string _TransformExtaintion;
	string defultExtaintion = "mp4";

	cout << "The defuilt File extention :" << defultExtaintion << endl;
	cout << "Please enter file extension " << endl;
	getline(cin, _TransformExtaintion);
	cout << endl;
	if (_TransformExtaintion == " ")
	{
		return defultExtaintion;
	}
	else
	{
		return _TransformExtaintion;
	}
}


int main()
{

	Desin();
	vector<string> myVideosPaths = FilePath();
	string savePath = outPutPath();
	string extention = TransformExtaintion();
	string platform = Platform_PUP();
	int targetBitrate = VideoQuality();

	cout << "\n================= PROCESSING START =================\n";

	for (int i = 0; i < myVideosPaths.size(); i++)
	{
		cout << "\n--- Processing Video (" << i + 1 << " of " << myVideosPaths.size() << ") ---" << endl;

		// بنخلق كائن ديناميكي للمسار الحالي في اللفة
		// cout << " 'FileName' ,  'Size' ,  'outPutPath' ,  'TransformExtaintion' ,  'Platform' ,  'Bitrate' ";
		clsVideoAsset dynamicVideo(myVideosPaths[i], 0.0, savePath, extention, platform, targetBitrate);

		// بنشغل الضغط للمسار ده
		dynamicVideo.ProcessAsset();
	}

	cout << "\n==================================================\n";

	system("pause>0");
	return 0;
}
