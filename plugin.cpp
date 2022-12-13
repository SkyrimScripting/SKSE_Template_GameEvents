#include <spdlog/sinks/basic_file_sink.h>

namespace logger = SKSE::log;

void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) {
        SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
        return;
    }
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::info);
}

// Our class which received game events
//
// Must have a *public* class inheritance for templated BSTEventSink<EVENT TYPE>
// for each event type you would like to receive.
//
// Also must have a `ProcessEvent` function which received a const pointer to one of the <EVENT TYPE>
//
// `ProcessEvent` is used to... well... process the event! You can do whatever you want with it :)
//
// It is not required to make your class a singleton, but it is very helpful!
// Otherwise, you need to be aware of where your class instance is instantiated and keep it alive.
class EventProcessor : public RE::BSTEventSink<RE::TESActivateEvent>, public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
    // Pretty typical singleton setup
    // *Private* constructor/destructor
    // And we *delete* the copy constructors and move constructors.
    EventProcessor() = default;
    ~EventProcessor() = default;
    EventProcessor(const EventProcessor&) = delete;
    EventProcessor(EventProcessor&&) = delete;
    EventProcessor& operator=(const EventProcessor&) = delete;
    EventProcessor& operator=(EventProcessor&&) = delete;

public:
    // Returns a reference to the one and only instance of EventProcessor :)
    //
    // Note: this is returned as a & reference. When you need this as a pointer, you'll want to use & (see below)
    static EventProcessor& GetSingleton() {
        static EventProcessor singleton;
        return singleton;
    }

    // Log information about Activate events that happen in the game
    RE::BSEventNotifyControl ProcessEvent(const RE::TESActivateEvent* event,
                                          RE::BSTEventSource<RE::TESActivateEvent>*) override {
        logger::info("{} activated {}", event->actionRef.get()->GetBaseObject()->GetName(),
                     event->objectActivated.get()->GetBaseObject()->GetName());
        return RE::BSEventNotifyControl::kContinue;
    }

    // Log information about Menu open/close events that happen in the game
    RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* event,
                                          RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override {
        logger::info("Menu {} Open? {}", event->menuName, event->opening);
        return RE::BSEventNotifyControl::kContinue;
    }
};

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SetupLog();

    // Get a reference to our Event Processor singleton
    auto& eventProcessor = EventProcessor::GetSingleton();

    // Listen for Activate events!
    //
    // For more events, I recommend searching CommonLibSSE for files starting with TESEvent
    //
    // 1. Visit this link: https://github.com/CharmedBaryon/CommonLibSSE-NG
    // 2. Press the "T" key to open the fuzzy find file search
    // 3. Type "TESEvent" (without the " quotes)
    // 4. Choose any of the files that show up! They're probably events that you can get via an event sink :)
    RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESActivateEvent>(&eventProcessor);

    // Note: a few UI events are registered via RE::UI instead of via RE::ScriptEventSourceHolder
    // - MenuOpenCloseEvent
    // - MenuModeChangeEvent>
    // - MenuModeCounterChangedEvent (use <void*> for template and cast)
    // - TutorialEvent               (use <void*> for template and cast)
    RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(&eventProcessor);

    return true;
}
