#include <QtPlugin>

#ifdef __linux__
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
#elif _WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

int main(int argc, char* argv[])
{
}
