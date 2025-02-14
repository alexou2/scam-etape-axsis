use btleplug::api::{Central, Manager as _, Peripheral, WriteType};
use btleplug::platform::{Adapter, Manager};
// use uuid::Uuid;
use tokio::time::Duration;
use uuid::Uuid;

#[tokio::main]
async fn main() {
    let manager = Manager::new().await.expect("Failed to create BLE manager");
    let adapters = manager.adapters().await.expect("Failed to get adapters");
    let adapter = adapters.into_iter().next().expect("No Bluetooth adapter found");

    println!("owowo {:?}", adapter);

    adapter.start_scan(Default::default()).await.expect("Failed to start scan");
    tokio::time::sleep(Duration::from_secs(3)).await; // Wait for scan results
    let peripherals = adapter.peripherals().await.expect("Failed to get peripherals");
    
    for peripheral in peripherals {
        let properties = peripheral.properties().await.expect("Failed to get properties");
        
                let is_connected = peripheral.is_connected().await.unwrap();
                let local_name = properties.clone()
                    .unwrap()
                    .local_name
                    .unwrap_or(String::from("(peripheral name unknown)"));
                println!(
                    "Peripheral {:?} is connected: {:?}",
                    &local_name, is_connected
                );

        
        
        if let Some(name) = properties.and_then(|p| p.local_name) {
            println!("Found device: {}", name);
            if name == "Pixel 7" {
                connect_and_send(&peripheral).await;
            }
        }
    }
}

async fn connect_and_send(peripheral: &impl Peripheral) {

    
    peripheral.discover_services().await.expect("Failed to discover services");

    
    peripheral.connect().await.expect("Failed to connect");
    

}