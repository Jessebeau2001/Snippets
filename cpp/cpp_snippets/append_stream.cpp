// File appender

using <iostream>

ifstream appendStream()
{
    ifstream stream{};
    string path{};

    cout << "Please enter a valid file path: ";
    getline(cin, path);
    while ((stream = ifstream{path}).is_open() == false) {
        cout << "file '"<< path << "' could not be found, please try again: ";
        getline(cin, path);
    }

    cout << "Opening '" << path << "'" << std::endl;
    return stream;
}
