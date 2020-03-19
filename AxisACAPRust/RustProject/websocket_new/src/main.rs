extern crate syslog;

use std::thread;
use websocket::sync::Server;
use websocket::OwnedMessage;
use syslog::{Facility, Formatter3164};
use log::{info};

fn write_to_syslog(message_temp: String) {
   let formatter = Formatter3164 {
        facility: Facility::LOG_USER,
        hostname: None,
        process: "axis_acapwith_rust".into(),
        pid: 0,
    };

    match syslog::unix(formatter) {
        Err(e) => println!("impossible to connect to syslog: {:?}", e),
        Ok(mut writer) => {
            writer.err(&message_temp).expect("could not write error message");
        }
    }
}

fn main() {
	info!("Starting websocket at {:?}", "Office");
	let server = Server::bind("192.168.1.150:2794").unwrap();
    
	for request in server.filter_map(Result::ok) {
		// Spawn a new thread for each connection.
		thread::spawn(|| {
			if !request.protocols().contains(&"rust-websocket".to_string()) {
				request.reject().unwrap();
				return;
			}

			let mut client = request.use_protocol("rust-websocket").accept().unwrap();

			let ip = client.peer_addr().unwrap();

			println!("Connection from {}", ip);
			let message = String::from("Connection from ".to_owned()+&(ip.to_string()));			
			write_to_syslog(message);
            // Let's print all the names to stdout.
            let message = OwnedMessage::Text("Hello".to_string() +" "+ &ip.to_string());
			     client.send_message(&message).unwrap();
			
			

			let (mut receiver, mut sender) = client.split().unwrap();

			for message in receiver.incoming_messages() {
				let message = message.unwrap();

				match message {
					OwnedMessage::Close(_) => {
						let message = OwnedMessage::Close(None);
						sender.send_message(&message).unwrap();
						println!("Client {} disconnected", ip);
						return;
					}
					OwnedMessage::Ping(ping) => {
						let message = OwnedMessage::Pong(ping);                       
						sender.send_message(&message).unwrap();
					}
					_ => {
					sender.send_message(&message).unwrap();
					println!("Message recieved {:?}", &message);
					},
				}
			}
		});
	}
}