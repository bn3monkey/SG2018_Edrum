from django.http import HttpResponse
from django.contrib.auth import login,logout,authenticate
from django.template import RequestContext
from django.shortcuts import render,redirect

from rest_framework import viewsets
from rest_framework import status
#from rest_framework_filters import backends
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated, AllowAny, IsAdminUser

from edrum_server_app.models import NoteFileModel, User
from edrum_server_app.serializers import NoteFileSerializer, UserSerializer, LoginSerializer, RedundantSerializer
#from edrum_server_app.filters import NoteFileFilter
from edrum_server_app.pretty_request import pretty_request

class NoteFileViewSet(viewsets.ModelViewSet) :
    queryset = NoteFileModel.objects.all()
    serializer_class = NoteFileSerializer

    #filter_backends = (backends.DjangoFilterBackend,)
    #filter_class = NoteFileFilter

    #def create(self, request, pk = None):
        #f = open("Log2.txt", "w")
        #f.write(pretty_request(request))
        #f.close()
        #serializer = NoteFileSerializer(data=request.data)
        #if serializer.is_valid():
        #    serializer.Meta.model(request.data).save()
        #return Response()
# Create your views here.

class LoginViewSet(viewsets.ModelViewSet):
    permission_classes = (AllowAny,)
    queryset = User.objects.all()
    serializer_class = LoginSerializer

    def list(self,request):
        return Response()

    def create(self,request,pk=None):
        user_id = request.data['user_id']
        password = request.data['password']

        print(user_id,file=sys.stderr)
        print(password,file=sys.stderr)
        
        user = authenticate(user_id = user_id, password = password)

        if user is not None:
            login(request,user)