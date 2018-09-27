#include "VolumeControl_2.h"
#include <atltrace.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qpixmapcache.h>
#include <qstylefactory>

VolumeControl_2::VolumeControl_2(QWidget *parent) : QMainWindow(parent), ui(new Ui::VolumeControl_2Class)
{

	QIcon icon("Resources/appicon.ico");
	this->setWindowIcon(icon);

	qApp->setStyle(QStyleFactory::create("Fusion"));

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
	darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	qApp->setPalette(darkPalette);

	qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	ui->setupUi(this);

	comboboxes.push_back(ui->ComboBox1);
	comboboxes.push_back(ui->ComboBox2);
	comboboxes.push_back(ui->ComboBox3);
	comboboxes.push_back(ui->ComboBox4);

	sliders.push_back(ui->Slider1);
	sliders.push_back(ui->Slider2);
	sliders.push_back(ui->Slider3);
	sliders.push_back(ui->Slider4);

	config_file.selectFile(ConfigFile::getDirectoryPath() + config_file_path);

	refresh_applications();
	time_thread = std::thread(&VolumeControl_2::time_task_A,this);

	this->setFixedSize(this->size());
}

void VolumeControl_2::on_ComboBox1_activated(int index) {
	on_combobox_activated(1, ui->ComboBox1->currentText());
}

void VolumeControl_2::on_ComboBox2_activated(int index) {
	on_combobox_activated(2, ui->ComboBox2->currentText());
}

void VolumeControl_2::on_ComboBox3_activated(int index) {
	on_combobox_activated(3, ui->ComboBox3->currentText());
}

void VolumeControl_2::on_ComboBox4_activated(int index) {
	on_combobox_activated(4, ui->ComboBox4->currentText());
}

void VolumeControl_2::on_Slider1_valueChanged(int value) {
	change_volume(1, value);
}

void VolumeControl_2::on_Slider2_valueChanged(int value) {
	change_volume(2, value);
}

void VolumeControl_2::on_Slider3_valueChanged(int value) {
	change_volume(3, value);
}

void VolumeControl_2::on_Slider4_valueChanged(int value) {
	change_volume(4, value);
}

bool VolumeControl_2::time_tick(time_t time)
{
	if ((time / TIME_REFRESH_APPLICATIONS) > refreshed_applications) {
		refresh_applications();
		refreshed_applications++;
		return true;
	}
	return false;
}

VolumeControl_2::~VolumeControl_2()
{
	run_time_task = false;
	time_thread.join();
}

void VolumeControl_2::on_combobox_activated(int box, QString process_name)
{
	size_t index = get_session_data_index(process_name);
	if (index == session_data.size()) set_slider_val(box - 1, get_master_volume());
	else {
		if (index == 0) {
			serial_in.queue_image(IconManager::get_image(session_data[index].path, 1, 1), (box - 1));
			set_slider_val(box - 1, 0.0);
		}
		else {
			if (!already_chosen(index, box - 1)) {
				set_slider_val(box - 1, session_data[index].master_volume * 100.0);
				serial_in.queue_image(IconManager::get_image(session_data[index].path, 32, 32), (box - 1));
			}
			else {
				comboboxes[box - 1]->setCurrentIndex(0);
				set_slider_val(box - 1, 0.0);
			}
		}
	}
}

bool VolumeControl_2::change_volume(int box, int value) {
	QString current_text = comboboxes[box - 1]->currentText();
	int index = get_session_data_index(current_text);
	if (index == session_data.size()) {
		set_master_volume((float)value / 100);
		return true;
	}
	else {
		if (index > 0) {
			float value_f = (float)value / 100;
			session_data[index].simple_audio_volume->SetMasterVolume(value_f, NULL);
			session_data[index].master_volume = value_f;
			return true;
		}
		return false;
	}
}

bool VolumeControl_2::set_slider_val(int slider, int value)
{
	sliders[slider]->setValue(value);
	return true;
}

void VolumeControl_2::refresh_applications()
{
	AudioSessionData empty_data;
	empty_data.process_name = "";
	
	session_data = std::vector<AudioSessionData>();
	session_data.push_back(empty_data);

	std::vector<AudioSessionData> temp_vec = process_data.get_session_data();

	for (int i = 0; i < temp_vec.size(); i++) session_data.push_back(temp_vec[i]);

	CoInitialize(NULL);
	endpoint_volume = get_audio_endpoint_volume();

	QString master = "Master";

	std::vector<QString> session_strings;

	for (int i = 0; i < session_data.size(); i++) session_strings.push_back(QString::fromStdString(session_data[i].process_name));

	// MASTER VOLUME ENABLE
	//session_strings.push_back(master);

	for (int i = 0; i < comboboxes.size(); i++) {
		QComboBox* cb = comboboxes[i];

		std::vector<QString> session_strings_temp = session_strings;
		std::vector<QString> cb_strings;

		for (int i = 0; i < cb->count(); i++) cb_strings.push_back(cb->itemText(i));

		// Write items to Combobox that arent already there.
		while (session_strings_temp.size() > 0) {
			if (contains(cb_strings, session_strings_temp[0]))
				session_strings_temp.erase(session_strings_temp.begin());
			else {
				cb->addItem(session_strings_temp[0]);
				session_strings_temp.erase(session_strings_temp.begin());
			}
		}

		// Delete items from combobox that shouldnt be there.
		while (cb_strings.size() > 0) {
			if (contains(session_strings, cb_strings[0]))
				cb_strings.erase(cb_strings.begin());
			else {
				if (remove_cb_item(cb_strings[0], i))
					cb_strings.erase(cb_strings.begin());
			}
		}
	}

	midi_in.set_slider(ui->Slider1, 16);
	midi_in.set_slider(ui->Slider2, 17);
	midi_in.set_slider(ui->Slider3, 18);
	midi_in.set_slider(ui->Slider4, 19);
	midi_in.start_communication(0);

	serial_in.set_slider(ui->Slider1, 0);
	serial_in.set_slider(ui->Slider2, 1);
	serial_in.set_slider(ui->Slider3, 2);
	serial_in.set_slider(ui->Slider4, 3);

	std::string port_name = "\\\\.\\" + config_file.getConfigValue("PortName");
	char* cstr = new char[port_name.size() + 1];
	strcpy(cstr, port_name.c_str());
	serial_in.connect(cstr);
	delete [] cstr;
}

void VolumeControl_2::time_task_A() {
	time_t tick_count_start = GetTickCount();
	while (run_time_task) {
		time_t dT = GetTickCount() - tick_count_start;
		if (dT >= TICKS_TIME_TASK) {
			if(this->time_tick(dT))
				tick_count_start = GetTickCount();
		}
		Sleep(100);
	}
}

bool VolumeControl_2::contains(std::vector<QString> vec, QString qs) {
	for (int i = 0; i < vec.size(); i++) if (vec[i] == qs) return true;
	return false;
}

bool VolumeControl_2::remove_cb_item(QString qs, int combobox) {
	for (int i = 0; i < comboboxes[combobox]->count(); i++) {
		if (comboboxes[combobox]->itemText(i) == qs) {
			comboboxes[combobox]->removeItem(i);
			return true;
		}
	}
	return false;
}

bool VolumeControl_2::already_chosen(int index, int box) {
	for (int i = 0; i < comboboxes.size(); i++) {
		if (box != i && comboboxes[i]->currentIndex() == index) return true;
	}
	return false;
}

IAudioEndpointVolume* VolumeControl_2::get_audio_endpoint_volume() {
	IAudioEndpointVolume* result;
	IMMDevice *device;
	IMMDeviceEnumerator *device_enum;

	//CoInitialize(NULL);

	CoCreateInstance(
		__uuidof(MMDeviceEnumerator),
		NULL,
		CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void**)&device_enum
	);

	device_enum->GetDefaultAudioEndpoint(
		eRender,
		eConsole,
		&device
	);

	device->Activate(
		__uuidof(IAudioSessionManager2),
		CLSCTX_ALL,
		NULL,
		(void**)&result
	);

	return result;
}

void VolumeControl_2::set_master_volume(float volume) {
	endpoint_volume->SetMasterVolumeLevelScalar(volume, NULL);
}

float VolumeControl_2::get_master_volume() {
	float result = 0.0;
	endpoint_volume->GetMasterVolumeLevelScalar(&result);
	return result * 100.0;
}

size_t VolumeControl_2::get_session_data_index(QString path)
{
	size_t index = -1;
	for (int i = 0; i < session_data.size(); i++) {
		if (QString::fromStdString(session_data[i].process_name) == path) {
			index = i;
			break;
		}
	}
	return index;
}
