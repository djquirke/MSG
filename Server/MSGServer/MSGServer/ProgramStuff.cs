using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace MSGServer
{
    // State object for reading client data asynchronously
    public class StateObject {
        // Client  socket.
        public Socket workSocket = null;
        // Size of receive buffer.
        public const int BufferSize = 1024;
        // Receive buffer.
        public byte[] buffer = new byte[BufferSize];
        // Received data string.
        public StringBuilder sb = new StringBuilder();
        public EndPoint ep;
    }

    public class AsynchronousTCPSocketListener
    {
        // Thread signal.
        // TODO: Why do we need this?
        public static ManualResetEvent allDone = new ManualResetEvent(false);

        public AsynchronousTCPSocketListener()
        {
        }

        public static void StartListening()
        {
            // Data buffer for incoming data.
            byte[] bytes = new Byte[1024];

            // Establish the local endpoint for the socket.
            IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            IPAddress ipAddress = ipHostInfo.AddressList[2];
            IPEndPoint localEndPoint = new IPEndPoint(ipAddress, Program.PORT);

            // Create a TCP/IP socket.
            Socket listener = new Socket(ipAddress.AddressFamily,
                SocketType.Stream, ProtocolType.Tcp);

            // Bind the socket to the local endpoint and listen for incoming connections.
            try
            {
                listener.Bind(localEndPoint);
                listener.Listen(100); // backlog

                while (true)
                {
                    // Set the event to nonsignaled state.
                    allDone.Reset();

                    // Start an asynchronous socket to listen for connections.
                    Console.WriteLine("Waiting for a connection...");
                    listener.BeginAccept(
                        new AsyncCallback(AcceptCallback),
                        listener);

                    // Wait until a connection is made before continuing.
                    allDone.WaitOne();
                }

            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            Console.WriteLine("\nPress ENTER to continue...");
            Console.Read();

        }

        public static void AcceptCallback(IAsyncResult ar)
        {
            // Signal the main thread to continue.
            allDone.Set();

            // Get the socket that handles the client request.
            Socket listener = (Socket)ar.AsyncState;
            Socket handler = listener.EndAccept(ar);

            IPEndPoint remote = handler.RemoteEndPoint as IPEndPoint;
            Console.Write("Connection established with IP:{0} on port:{1}\n", remote.Address, remote.Port);

            // Create the state object.
            StateObject state = new StateObject();
            state.workSocket = handler;
            handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                new AsyncCallback(ReadCallback), state);
        }

        public static void ReadCallback(IAsyncResult ar)
        {
            String content = String.Empty;

            // Retrieve the state object and the handler socket
            // from the asynchronous state object.
            StateObject state = (StateObject)ar.AsyncState;
            Socket handler = state.workSocket;

            // Read data from the client socket. 
            int bytesRead = handler.EndReceive(ar);

            if (bytesRead > 0)
            {
                // There  might be more data, so store the data received so far.
                state.sb.Append(Encoding.ASCII.GetString(state.buffer, 0, bytesRead));

                // Check for end-of-file tag. If it is not there, read 
                // more data.
                content = state.sb.ToString();
                if (content.IndexOf('\n') > -1)
                {
                    // All the data has been read from the 
                    // client. Display it on the console.
                    Console.Write("Read {0} bytes from socket. \n Data : {1} \n",
                        content.Length, content);
                    // Echo the data back to the client.
                    //Send(handler, content);
                    char [] delimiters = { ':' };
                    String[] parts = content.Split(delimiters);
                    if (parts[0].Equals("reg"))
                    {
                        // TODO
                        
                    }
                    if (parts[0].Equals("unreg"))
                    {
                        // TODO
                    }
                    if (parts[0].Equals("sendto"))
                    {
                        // TODO
                    }
                    if (parts[0].Equals("sendall"))
                    {
                        // TODO
                    }

                    if (parts[0].Equals("quit"))
                    {
                        IPEndPoint remote = handler.RemoteEndPoint as IPEndPoint;
                        Console.WriteLine("Client IP: " + remote.Address + " port: " + remote.Port);

                        Console.WriteLine("quit");
                        handler.Shutdown(SocketShutdown.Both);
                        handler.Close();
                    }
                    else
                    {
                        state.sb = new StringBuilder();
                        //state.workSocket = handler;
                        handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                            new AsyncCallback(ReadCallback), state);
                    }
                }
                else
                {
                    // Not all data received. Get more.
                    handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                        new AsyncCallback(ReadCallback), state);
                }

            }
        }

        private static void Send(Socket handler, string content)
        {
            byte[] buffer = Encoding.ASCII.GetBytes(content);
            handler.Send(buffer);
        }

        
        public static Hashtable clientsList = new Hashtable(); 

        // ...
        // TODO: write an asynchronous send function and a broadcast function.

    }

    // TODO: write a main

}
