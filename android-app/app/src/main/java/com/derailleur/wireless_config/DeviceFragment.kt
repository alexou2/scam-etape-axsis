package com.derailleur.wireless_config

import android.os.Bundle
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.derailleur.wireless_config.placeholder.PlaceholderContent
//
///**
// * A fragment representing a list of Items.
// */
//class DeviceFragment : Fragment() {
//
//    private var columnCount = 1
//
//    override fun onCreate(savedInstanceState: Bundle?) {
//        super.onCreate(savedInstanceState)
//
//        arguments?.let {
//            columnCount = it.getInt(ARG_COLUMN_COUNT)
//        }
//    }
//
//    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
//                              savedInstanceState: Bundle?): View? {
//        val view = inflater.inflate(R.layout.fragment_item_list, container, false)
//
//        // Set the adapter
//        if (view is RecyclerView) {
//            with(view) {
//                layoutManager = when {
//                    columnCount <= 1 -> LinearLayoutManager(context)
//                    else -> GridLayoutManager(context, columnCount)
//                }
//                adapter = MyDeviceRecyclerViewAdapter(PlaceholderContent.ITEMS)
//            }
//        }
//        return view
//    }
//
//    companion object {
//
//        // TODO: Customize parameter argument names
//        const val ARG_COLUMN_COUNT = "column-count"
//
//        // TODO: Customize parameter initialization
//        @JvmStatic
//        fun newInstance(columnCount: Int) =
//                DeviceFragment().apply {
//                    arguments = Bundle().apply {
//                        putInt(ARG_COLUMN_COUNT, columnCount)
//                    }
//                }
//    }
//}

import android.Manifest
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothManager
import android.bluetooth.le.*
import android.content.pm.PackageManager
import android.os.Build
import android.os.Handler
import android.os.Looper
import android.widget.Toast
import androidx.activity.result.contract.ActivityResultContracts
import androidx.core.app.ActivityCompat

class DeviceFragment : Fragment() {

    private lateinit var bluetoothAdapter: BluetoothAdapter
    private lateinit var bleScanner: BluetoothLeScanner
    private lateinit var deviceAdapter: MyDeviceRecyclerViewAdapter
    private val devices = mutableListOf<BluetoothDeviceItem>()

    private val handler = Handler(Looper.getMainLooper())
    private var scanning = false
    private val SCAN_PERIOD: Long = 10000 // Scan for 10 seconds

    private val bleScanCallback = object : ScanCallback() {
        override fun onScanResult(callbackType: Int, result: ScanResult) {
            val device = result.device
            if (device.name != null && devices.none { it.address == device.address }) {
                devices.add(BluetoothDeviceItem(device.name, device.address))
                deviceAdapter.notifyDataSetChanged()
            }
        }

        override fun onScanFailed(errorCode: Int) {
            Toast.makeText(context, "Scan failed: $errorCode", Toast.LENGTH_SHORT).show()
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val view = inflater.inflate(R.layout.fragment_item_list, container, false)

        val bluetoothManager = requireContext().getSystemService(BluetoothManager::class.java)
        bluetoothAdapter = bluetoothManager.adapter
        bleScanner = bluetoothAdapter.bluetoothLeScanner

        val recyclerView = view.findViewById<RecyclerView>(R.id.list)
        recyclerView.layoutManager = LinearLayoutManager(context)

        deviceAdapter = MyDeviceRecyclerViewAdapter(devices)
        recyclerView.adapter = deviceAdapter

        checkPermissionsAndStartScan()

        return view
    }

    private fun checkPermissionsAndStartScan() {
        val permissions = mutableListOf(
            Manifest.permission.BLUETOOTH_SCAN,
            Manifest.permission.BLUETOOTH_CONNECT,
            Manifest.permission.ACCESS_FINE_LOCATION
        )

        val requestPermissionLauncher = registerForActivityResult(
            ActivityResultContracts.RequestMultiplePermissions()
        ) { permissionsMap ->
            if (permissionsMap.all { it.value }) {
                startBleScan()
            } else {
                Toast.makeText(context, "Permissions denied", Toast.LENGTH_SHORT).show()
            }
        }

        if (permissions.any {
                ActivityCompat.checkSelfPermission(requireContext(), it) != PackageManager.PERMISSION_GRANTED
            }) {
            requestPermissionLauncher.launch(permissions.toTypedArray())
        } else {
            startBleScan()
        }
    }

    private fun startBleScan() {
        if (!scanning) {
            handler.postDelayed({
                scanning = false
                bleScanner.stopScan(bleScanCallback)
                Toast.makeText(context, "Scan stopped", Toast.LENGTH_SHORT).show()
            }, SCAN_PERIOD)

            scanning = true
            devices.clear()
            bleScanner.startScan(null, ScanSettings.Builder().setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY).build(), bleScanCallback)
            Toast.makeText(context, "Scanning for devices...", Toast.LENGTH_SHORT).show()
        }
    }
}
