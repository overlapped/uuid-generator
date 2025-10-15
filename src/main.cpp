#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMemoryResource.h>
#include <Wt/WPushButton.h>
#include <Wt/WServer.h>
#include <Wt/WText.h>

#include "UUIDGenerator.h"

class UUIDApplication : public Wt::WApplication {
public:
    UUIDApplication(const Wt::WEnvironment &env)
        : Wt::WApplication(env) {

        setTitle("UUID Generator Online Tool");

        // Create main container
        auto container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
        container->setStyleClass("container");

        // Add title
        auto title = container->addWidget(std::make_unique<Wt::WText>("<h1>UUID Generator</h1>"));
        title->setStyleClass("title");

        container->addWidget(std::make_unique<Wt::WBreak>());
        container->addWidget(std::make_unique<Wt::WBreak>());

        // Add description
        auto description = container->addWidget(std::make_unique<Wt::WText>(
            "Generate random UUIDs (Universally Unique Identifiers)"));
        description->setStyleClass("description");

        container->addWidget(std::make_unique<Wt::WBreak>());
        container->addWidget(std::make_unique<Wt::WBreak>());

        // Add label for UUID field
        auto uuidLabel = container->addWidget(std::make_unique<Wt::WText>("Generated UUID:"));
        uuidLabel->setStyleClass("label");

        container->addWidget(std::make_unique<Wt::WBreak>());

        // Create UUID display field
        uuidEdit_ = container->addWidget(std::make_unique<Wt::WLineEdit>());
        uuidEdit_->setTextSize(36);
        uuidEdit_->setReadOnly(true);
        uuidEdit_->setStyleClass("uuid-field");

        container->addWidget(std::make_unique<Wt::WBreak>());
        container->addWidget(std::make_unique<Wt::WBreak>());

        // Create generate button
        generateButton_ = container->addWidget(std::make_unique<Wt::WPushButton>("Generate New UUID"));
        generateButton_->setStyleClass("generate-btn");

        container->addWidget(std::make_unique<Wt::WBreak>());
        container->addWidget(std::make_unique<Wt::WBreak>());

        // Add some styling
        this->useStyleSheet("styles.css");

        // Connect button click to generate UUID
        generateButton_->clicked().connect(this, &UUIDApplication::generateUUID);

        // Generate initial UUID
        generateUUID();
    }

private:
    Wt::WLineEdit *uuidEdit_;
    Wt::WPushButton *generateButton_;

    void generateUUID() {
        std::string uuid = UUIDGenerator::generateUUID();
        uuidEdit_->setText(uuid);
    }
};

// Custom CSS styles
std::string CSS_STYLES = R"(
.container {
    max-width: 800px;
    margin: 0 auto;
    padding: 20px;
    font-family: Arial, sans-serif;
}

.title {
    text-align: center;
    color: #333;
    margin-bottom: 20px;
}

.description {
    text-align: center;
    color: #666;
    font-size: 16px;
}

.label {
    font-weight: bold;
    color: #333;
    font-size: 14px;
}

.uuid-field {
    width: 100%;
    padding: 12px;
    font-size: 16px;
    font-family: monospace;
    text-align: center;
    border: 2px solid #ddd;
    border-radius: 4px;
    background-color: #f9f9f9;
    margin: 10px 0;
}

.generate-btn {
    background-color: #4CAF50;
    border: none;
    color: white;
    padding: 15px 32px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 4px 2px;
    cursor: pointer;
    border-radius: 4px;
    transition: background-color 0.3s;
}

.generate-btn:hover {
    background-color: #45a049;
}
)";

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment &env) {
    auto app = std::make_unique<UUIDApplication>(env);
    return app;
}

int main(int argc, char **argv) {
    try {
        // Create server instance
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        // Add custom CSS
        std::vector<unsigned char> css(CSS_STYLES.begin(), CSS_STYLES.end());
        server.addResource(std::make_shared<Wt::WMemoryResource>("text/css", css), "styles.css");

        // Configure server
        server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

        // Start server
        if (server.start()) {
            int sig = Wt::WServer::waitForShutdown();
            std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
            server.stop();
        }
        // server.run();
    } catch (Wt::WServer::Exception &e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
        return 1;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
