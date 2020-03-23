extern crate dbus;
extern crate syslog;

use dbus::blocking::Connection;
use std::time::Duration;
use syslog::{Facility, Formatter3164};

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

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // First open up a connection to the session bus.
    let conn = Connection::new_session()?;

    // Second, create a wrapper struct around the connection that makes it easy
    // to send method calls to a specific destination and path.
    let proxy = conn.with_proxy("com.axis.ImageControl", "/", Duration::from_millis(5000));

    // Now make the method call. The ListNames method call takes zero input parameters and 
    // one output parameter which is an array of strings.
    // Therefore the input is a zero tuple "()", and the output is a single tuple "(names,)".
    let (names,): (Vec<String>,) = proxy.method_call("com.axis.ImageControl", "ListNames", ())?;

    // Let's print all the names to stdout.
    for name in names { 
        println!("{}", name); 
        write_to_syslog(name);
        }

    Ok(())
}