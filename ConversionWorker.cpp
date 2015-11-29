//
// Created by phitherek on 20.11.15.
//

#include <gtkmm/textview.h>
#include <glibmm/fileutils.h>
#include <glibmm/regex.h>
#include "ConversionWorker.h"
#include "Converter.h"
#include "ConversionError.h"
#include <sstream>
#include <gtkmm/progressbar.h>
#include <iostream>
#include <chrono>
#include <thread>

ConversionWorker::ConversionWorker(): _indir(""), _outdir(""), _cont(false), _mutex(), _thread(0), _builder(0), _conversionlogbuffer(0) {}


ConversionWorker::~ConversionWorker() {
    Glib::Threads::Mutex::Lock lock(_mutex);
    _cont = false;
    _thread->join();
    _conversionlogbuffer.reset();
    _builder.reset();
}



void ConversionWorker::start(Glib::RefPtr<Gtk::Builder> builder) {
    _builder = builder;
    _thread = Glib::Threads::Thread::create(sigc::mem_fun(*this, &ConversionWorker::run));
}

void ConversionWorker::run() {
    Gtk::ProgressBar* conversionprogressbar = NULL;
    Gtk::Label* conversionprogress = NULL;
    Gtk::TextView* conversionlogtextview = NULL;
    _builder->get_widget("conversionprogressbar", conversionprogressbar);
    _builder->get_widget("conversionprogress", conversionprogress);
    _builder->get_widget("conversionlogtextview", conversionlogtextview);
    _conversionlogbuffer = Gtk::TextBuffer::create();
    {
        Glib::Threads::Mutex::Lock lock(_mutex);
        if(_indir != "" && _outdir != "") {
            _cont = true;
        } else {
            _conversionlogbuffer->insert_at_cursor("Could not start conversion: Input and output directories cannot be empty!\n");
            conversionlogtextview->set_buffer(_conversionlogbuffer);
            sig_done();
            return;
        }
    }
    if(_cont) {
        {
            Glib::Threads::Mutex::Lock lock(_mutex);
            _conversionlogbuffer->insert_at_cursor("Starting conversion...\n");
            conversionlogtextview->set_buffer(_conversionlogbuffer);
        }
        Glib::Dir dir(_indir);
        std::vector<std::string> dirContents, inputs, outputs;
        dirContents.assign(dir.begin(), dir.end());
        for(unsigned int i = 0; i < dirContents.size(); i++) {
            Glib::RefPtr<Glib::Regex> nameRegex = Glib::Regex::create("\\.map$");
            if(nameRegex->match(dirContents[i])) {
                inputs.push_back(dirContents[i]);
            }
        }
        unsigned int i = 0;
        while(_cont && i < inputs.size()) {
            std::string input = _indir + "/" + inputs[i];
            std::string output = _outdir + "/" + inputs[i];
            output.replace(output.length()-3, 3, "inf");
            std::stringstream status;
            status.str("");
            status << i+1 << "/" << inputs.size();
            {
                Glib::Threads::Mutex::Lock lock(_mutex);
                conversionprogress->set_text(status.str());
                conversionprogressbar->set_fraction(static_cast<double>(i+1)/inputs.size());
                _conversionlogbuffer->insert_at_cursor("Converting file " + inputs[i] + "... ");
                conversionlogtextview->set_buffer(_conversionlogbuffer);
            }
            Converter conv(input, output);
            try {
                conv.convert();
                {
                    Glib::Threads::Mutex::Lock lock(_mutex);
                    _conversionlogbuffer->insert_at_cursor("Success!\n");
                    conversionlogtextview->set_buffer(_conversionlogbuffer);
                }
            } catch(ConversionError& e) {
                std::string err = "";
                err += "\nError! ";
                err += e.what();
                err += "\n";
                {
                    Glib::Threads::Mutex::Lock lock(_mutex);
                    _conversionlogbuffer->insert_at_cursor(err);
                    conversionlogtextview->set_buffer(_conversionlogbuffer);
                }
            }
            i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        {
            Glib::Threads::Mutex::Lock lock(_mutex);
            if(i == inputs.size()) {
                _conversionlogbuffer->insert_at_cursor("Conversion done!\n");
                conversionlogtextview->set_buffer(_conversionlogbuffer);
            } else {
                _conversionlogbuffer->insert_at_cursor("Conversion cancelled!\n");
                conversionlogtextview->set_buffer(_conversionlogbuffer);
            }
        }
        _cont = false;
        sig_done();
    }
}
void ConversionWorker::cancel() {
    Glib::Threads::Mutex::Lock lock(_mutex);
    _cont = false;
}

bool ConversionWorker::running() {
    Glib::Threads::Mutex::Lock lock(_mutex);
    return _cont;
}
