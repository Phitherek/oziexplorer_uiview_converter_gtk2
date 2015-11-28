//
// Created by phitherek on 20.11.15.
//

#ifndef OZIEXPLORER_UIVIEW_CONVERTER_CONVERSIONWORKER_H
#define OZIEXPLORER_UIVIEW_CONVERTER_CONVERSIONWORKER_H

#include <string>
#include <glibmm/threads.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <glibmm/dispatcher.h>

class ConversionWorker {
private:
    std::string _indir;
    std::string _outdir;
    bool _cont;
    mutable Glib::Threads::Mutex _mutex;
    Glib::Threads::Thread* _thread;
    Glib::RefPtr<Gtk::Builder> _builder;
    Glib::RefPtr<Gtk::TextBuffer> _conversionlogbuffer;
public:
    ConversionWorker();
    ~ConversionWorker();
    void start(Glib::RefPtr<Gtk::Builder> builder);
    void cancel();
    bool running();

    const std::string &getIndir() const {
        return _indir;
    }

    void setIndir(const std::string &indir) {
        _indir = indir;
    }

    const std::string &getOutdir() const {
        return _outdir;
    }

    void setOutdir(const std::string &outdir) {
        _outdir = outdir;
    }

    void run();

    Glib::Dispatcher sig_done;
};


#endif //OZIEXPLORER_UIVIEW_CONVERTER_CONVERSIONWORKER_H
