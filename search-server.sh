hugo
npx findpage --site public
cd public
python3.12 -m http.server 3000
cd ..
echo "Server running at localhost:3000"
