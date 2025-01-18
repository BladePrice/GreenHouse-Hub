#!/usr/bin/env python3
from http.server import SimpleHTTPRequestHandler, HTTPServer
import json
import os

PORT = 80
SETTINGS_FILE = "settings.json"

class RequestHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/get-settings':
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.end_headers()

            if os.path.exists(SETTINGS_FILE):
                with open(SETTINGS_FILE, "r") as f:
                    settings = json.load(f)
            else:
                settings = {}

            self.wfile.write(json.dumps(settings).encode())

        else:
            super().do_GET()

    def do_POST(self):
        if self.path == '/save-settings':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            settings = json.loads(post_data)

            with open(SETTINGS_FILE, "w") as f:
                json.dump(settings, f)

            self.send_response(200)
            self.end_headers()
            self.wfile.write(b"Settings saved successfully")
        else:
            self.send_response(404)
            self.end_headers()

if __name__ == "__main__":
    with HTTPServer(("", PORT), RequestHandler) as httpd:
        print(f"Serving at port {PORT}")
        httpd.serve_forever()