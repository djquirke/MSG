using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace MSGServer
{
    class AsynchronousUDPSocketListener
    {

        public static ManualResetEvent allDone = new ManualResetEvent(false);

        public AsynchronousUDPSocketListener() { }

        public static void StartListening()
        {
            // Data buffer for incoming data.
            byte[] bytes = new Byte[1024];

            

            try
            {
                //listener.Listen(10);
                
                while (true)
                {
                    // Establish the local endpoint for the socket.
                    IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Any, Program.PORT);
            
                    // Create a UDP socket.
                    Socket listener = new Socket(AddressFamily.InterNetwork,
                    SocketType.Dgram, ProtocolType.Udp);
                    // Set the event to nonsignaled state.
                    listener.Bind(localEndPoint);
                    allDone.Reset();

                    // Start an asynchronous socket to listen for connections.
                    Console.WriteLine("Waiting for a UDP connection...");

                    IPEndPoint sender = new IPEndPoint(IPAddress.Any, 9046);
                    EndPoint tmpRemote = (EndPoint)sender;

                    int recv = listener.ReceiveFrom(bytes, ref tmpRemote);

                    Console.Write("Message recv from: {0}", tmpRemote.ToString());
                    Console.WriteLine(Encoding.ASCII.GetString(bytes, 0, recv));
                    listener.Connect(tmpRemote);
                    listener.Send(bytes);
                    listener.Close();
                    // Create the state object.
                    //StateObject state = new StateObject();
                    //state.workSocket = listener;
                    //state.ep = tmpRemote;
                    //state.workSocket.BeginReceiveFrom(state.buffer, 0, StateObject.BufferSize, 0, ref tmpRemote, new AsyncCallback(ReceiveCallback), state);//(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReceiveCallback), state);

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

        private static void ReceiveCallback(IAsyncResult ar)
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
                    Send(handler, content);
                    char[] delimiters = { ':' };
                    String[] parts = content.Split(delimiters);

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
                        state.workSocket = handler;
                        handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                            new AsyncCallback(ReceiveCallback), state);
                    }
                }
                else
                {
                    // Not all data received. Get more.
                    handler.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                        new AsyncCallback(ReceiveCallback), state);
                }

            }
        }

        private static void Send(Socket handler, string content)
        {
            handler.Send(Encoding.ASCII.GetBytes(content));
        }
    }
}
