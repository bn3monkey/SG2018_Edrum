from django.http import HttpResponse
from django.contrib.auth import login,logout,authenticate
from django.template import RequestContext
from django.shortcuts import render,redirect

from rest_framework import viewsets
from rest_framework import status
from rest_framework import mixins
#from rest_framework_filters import backends
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated, AllowAny, IsAdminUser

from edrum_server_app.models import NoteFileModel, User
from edrum_server_app.serializers import NoteFileSerializer, UserSerializer, LoginSerializer
from edrum_server_app.serializers import SignUpSerializer, RedundantSerializer
from edrum_server_app.filters import UserFilter
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

        # TO DO THIS PART
        if user is not None:
            login(request,user)
            content = {"content" : "Success"}
            return Response(content,status=status.HTTP_202_ACCEPTED)
        else:
            content = {"content" : "Fail"}
            return Response(content,status=status.HTTP_400_BAD_REQUEST)

class LogoutViewSet(mixins.ListModelMixin,viewsets.GenericViewSet):
    permission_classes = (IsAuthenticated,)
    queryset = User.objects.all()

    def list(self,request,pk=None):
        logout(request)
        success = {"Success" : "Yes"}
        return Response(success,status=status.HTTP_201_CREATED)

class SignUpViewSet(viewsets.ModelViewSet):
    permission_classes = (AllowAny,)
    queryset = User.objects.all()
    serializer_class = SignUpSerializer
    
    def list(self,request):
        return Response()
    # TO DO CREATE
    def create(self,request,pk=None):
        serializer = SignUpSerializer(data=request.data)
        if serializer.is_valid():
            serializer.create(request.data)
            success = {'Success':'Yes'}
            return Response(success,status=status.HTTP_201_CREATED)
        else:
            success = {'Success':'No'}
            return Response(success,status=status.HTTP_400_BAD_REQUEST)

class RedundantViewSet(viewsets.ModelViewSet):
    # RedundantSerializer only returns user_id
    # Only Check user_id
    permission_classes = (AllowAny,)
    queryset = User.objects.all()
    serializer_class = RedundantSerializer

    """
    def list(self,request):
        check_id = self.cleaned_data['user_id']
        if User.objects.filter(user_id=user_id).exists():
            raise
    """
    def list(self,request):
        user_id = request.data['user_id']
        if User.objects.filter(user_id=user_id).exists():
            success = {'Success':'False'}
            return Response(success,status=status.HTTP_400_BAD_REQUEST)
        else:
            # TO DO THIS PART