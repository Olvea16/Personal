#pragma once

#include <QtWidgets/QMainWindow>
#include <chrono>
#include <thread>
#include <unordered_map>
#include "ui_VolumeControl_2.h"
#include "ProcessData.h"
#include "MIDIIn.h"
#include "SerialIn.h"
#include "ConfigFile.h"

#define TIME_REFRESH_APPLICATIONS ((time_t)1000)
#define TICKS_TIME_TASK ((time_t)100)

class VolumeControl_2 : public QMainWindow
{
	Q_OBJECT

public:
	VolumeControl_2(QWidget *parent = Q_NULLPTR);
	~VolumeControl_2();

private:
	Ui::VolumeControl_2Class *ui;
	ProcessData process_data;
	std::vector<AudioSessionData> session_data;
	std::vector<QComboBox*> comboboxes;
	std::vector<QSlider*> sliders;
	IAudioEndpointVolume* endpoint_volume;
	MIDIIn midi_in;
	SerialIn serial_in;
	ConfigFile config_file;
	const std::string config_file_path = "\\config.ini";

	bool run_time_task = true;

	void on_combobox_activated(int box, QString process_name);
	bool change_volume(int box, int value);
	bool set_slider_val(int slider, int value);
	void refresh_applications();
	void time_task_A();
	bool time_tick(time_t time);
	bool contains(std::vector<QString> vec, QString qs);
	bool remove_cb_item(QString qs, int combobox);
	bool already_chosen(int index, int box);
	IAudioEndpointVolume* get_audio_endpoint_volume();
	void set_master_volume(float volume);
	float get_master_volume();
	size_t get_session_data_index(QString path);

	std::thread time_thread;

	int refreshed_applications = 0;

private slots: 
	void on_ComboBox1_activated(int index);
	void on_ComboBox2_activated(int index);
	void on_ComboBox3_activated(int index);
	void on_ComboBox4_activated(int index);

	void on_Slider1_valueChanged(int value);
	void on_Slider2_valueChanged(int value);
	void on_Slider3_valueChanged(int value);
	void on_Slider4_valueChanged(int value);
};
