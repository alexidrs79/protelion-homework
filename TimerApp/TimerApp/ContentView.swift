//
//  ContentView.swift
//  TimerApp
//
//  Created by Alexi Dermosesian on 06.11.26.
//

import SwiftUI
import TimerWrapper

struct ContentView: View {
    @State private var isRunning = false
    @State private var showAlert = false
    @State private var alertMessage = ""
    
    var body: some View {
        Button(action: buttonTapped) {
            Text(isRunning ? "STOP" : "START")
                .font(.title.bold())
                .foregroundStyle(.white)
                .frame(width: 200, height: 200)
                .background(isRunning ? Color.red : Color.green)
                .clipShape(Circle())
        }
        .alert(alertMessage, isPresented: $showAlert) {
            Button("OK") {
                isRunning = false
            }
            
        }
    }
    
    private func buttonTapped() {
        if isRunning {
            stopTimer()
        } else {
            startTimer()
        }
    }
    
    private func startTimer() {
        let result = TimerWrapper.start()
        if result == 0 {
            isRunning = true
        } else {
            alertMessage = "Could not start the timer."
            showAlert = true
        }
    }
    private func stopTimer() {
        let seconds = TimerWrapper.stop()
        if seconds >= 0 {
            alertMessage = "\(seconds) seconds have elapsed."
        } else {
            alertMessage = "The timer was not running."
        }
        showAlert = true
    }
}

#Preview {
    ContentView()
}
