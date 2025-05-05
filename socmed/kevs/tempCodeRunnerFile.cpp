                bool hasLikes = false;
                for (const string& like : currentUser->likes) {
                    if (find(user.likes.begin(), user.likes.end(), like) != user.likes.end()) {
                        cout << "    - " << like << "\n";
                        hasLikes = true;
                    }
                }
                if (!hasLikes) {
                    cout << "    None\n";
                    if (!user.likes.empty()) {
                        cout << "  Their Likes:\n";
                        for (const string& like : user.likes) {
                            cout << "    * " << like << "\n";
                        }
                    }
                }
